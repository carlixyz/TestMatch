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

	if (ATMGameMode)
	{
		ATMGameMode->Services->NotifyDataChange.AddDynamic(this, &USocialComponent::UpdateData);
	}

}

TArray<UFriendData*> USocialComponent::RequestInitialData()
{
	TArray<UFriendData*> friendsData;
	/// Retrieve here all Friends profiles from Services 
	// ATMGameMode->Services->ProvideInitialFriendData();
	// ...
	return friendsData;
}


void USocialComponent::UpdateData(TArray<FFriendStatus>& friendStats) // Struct Passed by Ref
{
	bool bStatusChanged = false;
	int32 friendsCount = FriendDataProfiles.Num();

	/// process here all the Profiles Status Info...
	if (FriendDataProfiles.IsEmpty() || friendsCount != friendStats.Num())
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
		for (int i = 0; i < friendsCount; i++)
		{
			/// If some local friend connection Status differs from Service's one 
			if (FriendDataProfiles[i]->ProfileStatus.bIsConnected != friendStats[i].bIsConnected)
			{
				/// Then Update Connection Status
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
		NotifyDataUpdate.ExecuteIfBound(textData); //NotifyDataUpdate.Broadcast(textData);
	}
	//if (GEngine)
	//{
	//	fProfiles[0].NickName = FString("HEY YOU OVERHERE");
	//	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Purple, fProfiles[0].NickName);
	//	FriendProfiles[0].NickName = FString("NEW NICKNAME");
	//	GEngine->AddOnScreenDebugMessage(-1, 15, FColor::Red, FriendProfiles[0].NickName);
	//}

}
