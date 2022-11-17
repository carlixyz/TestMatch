// Fill out your copyright notice in the Description page of Project Settings.


#include "ServicesComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/DataTable.h"
#include "../Structs/FriendStatus.h"
#include "UObject/ConstructorHelpers.h"

UServicesComponent::UServicesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	/// Load the Friend Profiles DataTable REFERENCE (Use Copy Reference REMEBER!)
	if (FriendsTable == nullptr)
	{
		FriendsTable = LoadTableRefFromPath(
			"DataTable'/Game/Blueprints/DataTables/DT_FriendsConnectionStatus.DT_FriendsConnectionStatus'");
	}
}

UDataTable* UServicesComponent::LoadTableRefFromPath(const FName& path)
{
	if (path == NAME_None)
		return nullptr;

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Yellow, *path.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Yellow, "Loading DataTable at path:");
	}

	return Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *path.ToString()));
}

void UServicesComponent::BeginPlay()
{
	Super::BeginPlay();

	/// Keep on a local array for handling random connection events
	FriendProfiles = ProcessFriendsRawDataTable(FriendsTable);

	/// Notify all PlayerControllers 
	//NotifyDataChange.Broadcast(FriendProfiles);

	/// We don't need a Tick function but a timer loop instead ...
	GetWorld()->GetTimerManager().SetTimer(AutoUpdateTimer,
										   this,
										   &UServicesComponent::ChangeRandomData,
										   AutoUpdateDelay,
										   false);
}

TArray<FFriendStatus> UServicesComponent::ProcessFriendsRawDataTable(UDataTable* friendsDataTable)
{
	if (friendsDataTable == nullptr && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,
										 15, 
										 FColor::Red, 
										 "Error Empty DataTable, Setup one on Services" );
		return TArray<FFriendStatus>();
	}

	/// First-time Parse DataTable & load into a local Array for convenience
	TArray<FName> rowNames = friendsDataTable->GetRowNames();
	TArray<FFriendStatus> friendsProfileStatus;

	for (FName rowName : rowNames)
	{
		/// Build up a friends Array for easier manipulation
		FFriendStatus* Item = friendsDataTable->FindRow<FFriendStatus>(rowName, "");
		if (Item)
			friendsProfileStatus.Add(*Item);
	}

	return friendsProfileStatus;
}


TArray<FFriendStatus>& UServicesComponent::RequestFriendsData()
{
	return FriendProfiles;
}

void UServicesComponent::ChangeRandomData()
{
	/// Choose Randomly an user & toggle it's connection Status
	int32 friendsCount = FriendProfiles.Num();

	if (friendsCount > 0)
	{
		int32 randomIndex = FMath::RandRange(0, friendsCount - 1);
		if (randomIndex == LastRandomIndex)
		{
			FMath::RandInit(FMath::GetRandSeed() - FMath::RandRange(0, 10000000));
			randomIndex = FMath::RandRange(0, friendsCount - 1);
		}

		/// Toggle connection Status
		FriendProfiles[randomIndex].bIsConnected = !FriendProfiles[randomIndex].bIsConnected;

		/// Notify all PlayerControllers about the new state
		NotifyDataChange.Broadcast(FriendProfiles);

		LastRandomIndex = randomIndex;
		//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, "NotifyDataChange.Broadcast(FriendProfiles);");
	}

	/// Launch timer loop again
	GetWorld()->GetTimerManager().SetTimer(AutoUpdateTimer,
										   this,
										   &UServicesComponent::ChangeRandomData,
										   AutoUpdateDelay,
										   false);
}


