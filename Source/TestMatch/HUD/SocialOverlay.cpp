// Fill out your copyright notice in the Description page of Project Settings.


#include "SocialOverlay.h"
#include "../TestMatchPlayerController.h"	//#include "GameFramework/PlayerController.h"
#include "../Components/SocialComponent.h"
#include "../Structs/FriendStatus.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"


void USocialOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OwningPlayer = GetOwningPlayer<APlayerController>(); // GetOwningPlayer<ATestMatchPlayerController>();

	if (InfoText && OwningPlayer)
	{
		//UE_LOG(LogTemp, Warning, TEXT("OnInitialized message"));

		/// Link with PlayerController' SocialComponent Notifies...
		ATestMatchPlayerController* playerController = Cast<ATestMatchPlayerController>(OwningPlayer);
		if (playerController && playerController->Social)
		{
			/// Retrieve the PlayerController To request the DataTable
			playerController->Social->NotifyDataUpdate.BindUFunction(this, "UpdateWidget");
			//playerController->Social->NotifyDataUpdate.BindUFunction(this, &USocialOverlay::UpdateWidget);

			UpdateWidgets( FString("PLAYER CONTROLLER FOUND"));

			//if(FriendOnlineEntryClass)
			//	NewObject<FriendOnlineEntryClass>()

		}
	}

}

void USocialOverlay::UpdateWidgets(FString text)
{
	/// Check & Refresh all widget displayed information


	SetDisplayText(text);


	/// Update Lists regarding connection status


	UpdateOnlineList();

	UpdateOfflineList();
}

void USocialOverlay::SetDisplayText(FString textToDisplay)
{
	if (InfoText)
	{
		InfoText->SetText(FText::FromString(textToDisplay));
	}
}

void USocialOverlay::UpdateOnlineList()
{

}

void USocialOverlay::UpdateOfflineList()
{

}

void USocialOverlay::SetFriendOnline(UObject* friendItem)
{
	if (OnlineList->GetListItems().Contains(friendItem))
		return;

	OnlineList->AddItem(friendItem);
	OfflineList->RemoveItem(friendItem);
}

void USocialOverlay::SetFriendOffline(UObject* friendItem)
{
	if (OfflineList->GetListItems().Contains(friendItem))
		return;

	OnlineList->RemoveItem(friendItem);
	OfflineList->AddItem(friendItem);
}
