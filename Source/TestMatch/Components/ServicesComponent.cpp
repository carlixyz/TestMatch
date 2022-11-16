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

void UServicesComponent::BeginPlay()
{
	Super::BeginPlay();

	if (FriendsTable == nullptr && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, "Error Empty DataTable, Set one on Services");
		return;
	}

	/// First-time Parse DataTable & load into local Array
	TArray<FName> rowNames = FriendsTable->GetRowNames();
	for (FName rowName : rowNames)
	{
		/// Build up a friends Array for easier manipulation
		FFriendStatus* Item = FriendsTable->FindRow<FFriendStatus>(rowName, "");
		if (Item)
			FriendProfiles.Add(*Item);

		//if (GEngine)
		//{
		////	int32 printIndex = FriendProfiles.Num() -1;
		//	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Purple, rowName.ToString());
		//	//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Purple, FriendProfiles[printIndex].NickName);
		//}
	}

	/// Notify all PlayerControllers 
	NotifyDataChange.Broadcast(FriendProfiles);

	// ...
	GetWorld()->GetTimerManager().SetTimer(AutoUpdateTimer,
										   this,
										   &UServicesComponent::ChangeRandomData,
										   AutoUpdateDelay,
										   false);
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

void UServicesComponent::ChangeRandomData()
{
	/// Choose Randomly an user & toggle it's connection Status
	int32 friendsCount = FriendProfiles.Num();

	if (friendsCount > 0)
	{
		int32 randomIndex = FMath::RandRange(0, friendsCount - 1);

		/// Toggle connection Status
		FriendProfiles[randomIndex].bIsConnected = !FriendProfiles[randomIndex].bIsConnected;

		/// Notify all PlayerControllers about the new state
		NotifyDataChange.Broadcast(FriendProfiles);

		//GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Green, "NotifyDataChange.Broadcast(FriendProfiles);");
	}

	/// Launch timer loop again
	GetWorld()->GetTimerManager().SetTimer(AutoUpdateTimer,
										   this,
										   &UServicesComponent::ChangeRandomData,
										   AutoUpdateDelay,
										   false);
}


