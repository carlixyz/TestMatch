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
		ATMGameMode->Services->NotifyDataChange.AddDynamic(this, &USocialComponent::OnDataChanged);
	}

}

void USocialComponent::OnDataChanged(TArray<FFriendStatus>& friendStats) // Struct Passed by Ref
{
	/*
	int32 friendsCount = FriendProfiles.Num();

	/// process here all the DataTable Info...
	if (FriendProfiles.IsEmpty() || friendsCount != fProfiles.Num())
	{
		/// If First time load Then Copy locally all data...
		FriendProfiles.Empty();
		FriendProfiles = fProfiles;

		FString textData = "friendProfiles Initialized!";
		NotifyDataUpdate.ExecuteIfBound(textData); //NotifyDataUpdate.Broadcast(textData);
	}
	else
	{
		bool bStatusChanged = false;
		for (int i = 0; i < friendsCount; i++)
		{
			/// If some local friend connection Status differs from Service's one 
			if (FriendProfiles[i].bIsConnected != fProfiles[i].bIsConnected)
			{
				FriendProfiles[i].bIsConnected = fProfiles[i].bIsConnected;
				/// then Notify it
				bStatusChanged = true;
			}
		}

		if (bStatusChanged)
		{
			FString textData = "friendProfiles Updated!";
			NotifyDataUpdate.ExecuteIfBound(textData); //NotifyDataUpdate.Broadcast(textData);
		}
	}
	*/

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
