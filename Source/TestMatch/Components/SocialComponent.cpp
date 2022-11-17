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
		Cast<ATestMatchGameMode>( UGameplayStatics::GetGameMode(GetWorld()) );

	if (ATMGameMode && ATMGameMode->Services)
	{
		FriendDataProfiles.Empty();
		
		TArray<FFriendStatus>& friendStatus = ATMGameMode->Services->RequestFriendsData();
		for (FFriendStatus fStats : friendStatus)
		{
			UFriendData* friendDataObject = NewObject<UFriendData>();
			friendDataObject->ProfileStatus = fStats;
			FriendDataProfiles.Add(friendDataObject);
		}

		ATMGameMode->Services->NotifyDataChange.AddDynamic(this, &USocialComponent::SyncData);
	}
}

TArray<UFriendData*> USocialComponent::GetInitialFriendData()
{
	/// Retrieve here all Friends profiles from Services 
	if (FriendDataProfiles.IsEmpty() && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,
										 15,
										 FColor::Red,
										 "Friends Status array is empty due connection error, Check on Services");
	}

	return FriendDataProfiles;
}


void USocialComponent::SyncData(TArray<FFriendStatus>& friendStats) // Struct Passed by Ref
{
	bool bStatusChanged = false;
	int32 cachedFriendsCount = FriendDataProfiles.Num();

	/// If there's a huge change on list count, process here all the Profiles Status Info again...
	if (FriendDataProfiles.IsEmpty() || cachedFriendsCount != friendStats.Num())
	{
		/// If First time load Then Copy locally all data...
		FriendDataProfiles.Empty();

		/// FriendDataProfiles = fProfiles;
		for (FFriendStatus fStats : friendStats)
		{
			UFriendData* friendDataObject = NewObject<UFriendData>();
			friendDataObject->ProfileStatus = fStats;
			FriendDataProfiles.Add(friendDataObject);
		}

		bStatusChanged = true;
	}
	else
	{
		for (int i = 0; i < cachedFriendsCount; i++)
		{
			// If some local friend connection Status differs from Service's one 
			if (FriendDataProfiles[i]->ProfileStatus.bIsConnected != friendStats[i].bIsConnected)
			{
				// Then Update Connection Status
				FriendDataProfiles[i]->ProfileStatus.bIsConnected = friendStats[i].bIsConnected;
				/// And Notify it
				bStatusChanged = true;

				/// If There's a new friend connected Online Send another Notify for that too.
				if (FriendDataProfiles[i]->ProfileStatus.bIsConnected && GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 20, FColor::Green,
													 FString::Printf(TEXT("%s is Online"),
													 *FriendDataProfiles[i]->ProfileStatus.FullName.ToString()) );
				}
			}
		}
	}
	

	if (bStatusChanged)
	{
		FString textData = "friendProfiles Updated!";
		NotifyDataSync.ExecuteIfBound(textData); //NotifyDataUpdate.Broadcast(textData);
	}
}
