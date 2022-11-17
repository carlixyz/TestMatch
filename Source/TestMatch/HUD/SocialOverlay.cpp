// Fill out your copyright notice in the Description page of Project Settings.


#include "SocialOverlay.h"
#include "../TestMatchPlayerController.h"
#include "../Components/SocialComponent.h"
#include "../Structs/FriendStatus.h"
#include "../Structs/FriendData.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"

void USocialOverlay::NativeConstruct()
{
	Super::NativeConstruct();


	InitDataLists();

}

void USocialOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OwningPlayer = GetOwningPlayer<APlayerController>(); // GetOwningPlayer<ATestMatchPlayerController>();

	if (InfoText && OwningPlayer)
	{
		/// Link with PlayerController' SocialComponent Notifies...
		ATestMatchPlayerController* playerController = Cast<ATestMatchPlayerController>(OwningPlayer);
		if (playerController && playerController->Social)
		{
			/// Retrieve the PlayerController To request the DataTable
			playerController->Social->NotifyDataUpdate.BindUFunction(this, "UpdateWidget");
			//playerController->Social->NotifyDataUpdate.BindUFunction(this, &USocialOverlay::UpdateWidget);

			UpdateWidgets(FString("PLAYER CONTROLLER FOUND"));
		}
	}

}

void USocialOverlay::InitDataLists()
{
	/// Should Request to SocialComponent Data
	// playerController->Social.RequestInitialData(); 

	TArray<class UFriendData*> FriendDataExamples;

	for (int i = 0; i < 3; i++)
	{
		UFriendData* fData = NewObject<UFriendData>();
		fData->ProfileStatus.NickName = FString("Charlie");
		FriendDataExamples.Add(fData);
	}

	if (OnlineList)
	{
		OnlineList->ClearListItems();
		OnlineList->SetListItems(FriendDataExamples);
		ToggleOnlineButton->OnClicked.AddDynamic(this, &USocialOverlay::ToggleOnlineListVisibility);
	}

	if (OfflineList)
	{
		OfflineList->ClearListItems();
		ToggleOfflineButton->OnClicked.AddDynamic(this, &USocialOverlay::ToggleOfflineListVisibility);
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

void USocialOverlay::ToggleOnlineListVisibility()
{
	if (OnlineList == nullptr) return;

	switch (OnlineList->GetVisibility())
	{
		case ESlateVisibility::Visible:
			OnlineList->SetVisibility(ESlateVisibility::Hidden);
			break;
		case ESlateVisibility::Hidden:
			OnlineList->SetVisibility(ESlateVisibility::Visible);
			break;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Button Clicked"));
}

void USocialOverlay::ToggleOfflineListVisibility()
{
	if (OfflineList == nullptr) return;

	switch (OfflineList->GetVisibility())
	{
	case ESlateVisibility::Visible:
		OfflineList->SetVisibility(ESlateVisibility::Hidden);
		break;
	case ESlateVisibility::Hidden:
		OfflineList->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}
