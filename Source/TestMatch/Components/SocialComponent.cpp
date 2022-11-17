// Fill out your copyright notice in the Description page of Project Settings.


#include "SocialComponent.h"
#include "ServicesComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../TestMatchGameMode.h"
#include "../Structs/FriendData.h"

USocialComponent::USocialComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USocialComponent::BeginPlay()
{
	Super::BeginPlay();

	/// Link with GameMode' Services Comp Notifies...
	ATestMatchGameMode* ATMGameMode =
		Cast<ATestMatchGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (ATMGameMode && ATMGameMode->Services)
	{
		/// This is a shortcut to Fill up quickly the local Data, If you want to use it uncomment
		//FriendsDataCache = ReFillDataCache(ATMGameMode->Services->ProvideFriendsData());

		ATMGameMode->Services->NotifyDataChange.AddDynamic(this, &USocialComponent::SyncData);
	}
}



TArray<UFriendData*> USocialComponent::GetInitialFriendData()
{
	/// Retrieve here all Friends profiles from Services 
	if (FriendsDataCache.IsEmpty() && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,
										 15,
										 FColor::Red,
										 "Hold on, Retrieving Friends Status Data from Services");
	}

	return FriendsDataCache;
}



TArray<UFriendData*> USocialComponent::ReFillDataCache(TArray<FFriendStatus>& friendStats)
{
	TArray<UFriendData*> friendsDataCache;

	for (FFriendStatus fStats : friendStats)
	{
		UFriendData* friendDataObject = NewObject<UFriendData>();
		friendDataObject->ProfileStatus = fStats;
		friendsDataCache.Add(friendDataObject);
	}

	return friendsDataCache;
}

void USocialComponent::SyncData(TArray<FFriendStatus>& friendStats) // Struct Passed by Ref
{
	int32 cachedFriendsCount = FriendsDataCache.Num();

	/// If there's a huge change between lists, SyncUp everything again...
	if (FriendsDataCache.IsEmpty() || cachedFriendsCount != friendStats.Num())
	{

		/// If First time load Then Copy locally all data...
		//FriendsDataCache.Empty();
		FriendsDataCache = ReFillDataCache(friendStats);
	}
	else
	{
		/// Else just keep checking every item status...
		for (int i = 0; i < cachedFriendsCount; i++)
		{
			// If some local friend connection Status differs from Service's one 
			if (FriendsDataCache[i]->ProfileStatus.bIsConnected != friendStats[i].bIsConnected)
			{
				// Then Update Connection Status
				FriendsDataCache[i]->ProfileStatus.bIsConnected = friendStats[i].bIsConnected;

				/// And Notify it
				NotifyDataSync.ExecuteIfBound(FriendsDataCache[i]); //NotifyDataUpdate.Broadcast(textData);
			}
		}
	}
}
