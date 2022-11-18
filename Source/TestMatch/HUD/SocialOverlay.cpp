// Fill out your copyright notice in the Description page of Project Settings.


#include "SocialOverlay.h"
#include "../TestMatchPlayerController.h"
#include "../Components/SocialComponent.h"
#include "../Structs/FriendStatus.h"
#include "../Structs/FriendData.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "ToastPopup.h"

void USocialOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OwningPlayer = Cast<ATestMatchPlayerController>(GetOwningPlayer<APlayerController>());

	if (OwningPlayer)
	{
		/// Link with PlayerController' SocialComponent Notifies...
		if (OwningPlayer && OwningPlayer->Social)
		{
			/// Retrieve the PlayerController To request all friends Profile Data
			InitListViewData(OwningPlayer->Social->GetInitialFriendData());

			/// Bind some Notifiers to keep track of any sudden connection
			OwningPlayer->Social->NotifyDataSync.BindUFunction(this, "UpdateFriendWidgets");
		}
	}
}

void USocialOverlay::InitListViewData(TArray<UFriendData*> friendsDataList)
{
	if (OnlineList && OfflineList)
	{
		OnlineList->ClearListItems();
		OfflineList->ClearListItems();

		for (auto friendProfile : friendsDataList)
			SetupFriendItem(friendProfile);				/// Add each friend item

		ToggleOnlineButton->OnClicked.AddDynamic(this, &USocialOverlay::ToggleOnlineListVisibility);
		ToggleOfflineButton->OnClicked.AddDynamic(this, &USocialOverlay::ToggleOfflineListVisibility);
	}
}

void USocialOverlay::UpdateFriendWidgets(UFriendData* friendData)
{
	/// Check & Refresh all widget displayed information


	/// If There's a new friend connected Online Send another Notify for that too.
	if (friendData->ProfileStatus.bIsConnected)
		AnnounceFriendOnline(friendData->ProfileStatus.NickName + FString(" is Online"));

	/// Update Lists regarding connection status
	SetupFriendItem(friendData);
}

void USocialOverlay::AnnounceFriendOnline(FString textToDisplay)
{
	if (ToastPopupClass && PopupArea)
	{
		//InfoText->SetText(FText::FromString(textToDisplay));
		UToastPopup* popup = Cast<UToastPopup>(CreateWidget(this, ToastPopupClass));

		if (popup)
		{
			PopupArea->AddChildToVerticalBox(popup);
			popup->SetupDisplayedName(textToDisplay);
		}

	}
}



void USocialOverlay::SetupFriendItem(UFriendData* friendItem)
{
	if (friendItem == nullptr) return;

	if (friendItem->ProfileStatus.bIsConnected)			/// Set Friend Online
	{
		if (OnlineList->GetListItems().Contains(friendItem))
			return;

		OnlineList->AddItem(friendItem);
		OfflineList->RemoveItem(friendItem);
	}
	else												/// Set Friend Offline
	{
		if (OfflineList->GetListItems().Contains(friendItem))
			return;

		OnlineList->RemoveItem(friendItem);
		OfflineList->AddItem(friendItem);
	}

	if (OnlineButtonText )
	{
		OnlineButtonText->SetText(FText::FromString(
			FString::Printf(TEXT("Toggle Online Players %d"), OnlineList->GetNumItems()) ));
	}

	if (OfflineButtonText)
	{
		OfflineButtonText->SetText(FText::FromString(
			FString::Printf(TEXT("Toggle Offline Players %d"), OfflineList->GetNumItems())));
	}
}

void USocialOverlay::ToggleOnlineListVisibility()
{
	if (OnlineList == nullptr) return;

	switch (OnlineList->GetVisibility())
	{
	case ESlateVisibility::Visible:
		OnlineList->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::Collapsed:
		OnlineList->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

void USocialOverlay::ToggleOfflineListVisibility()
{
	if (OfflineList == nullptr) return;

	switch (OfflineList->GetVisibility())
	{
		case ESlateVisibility::Visible:
			OfflineList->SetVisibility(ESlateVisibility::Collapsed);
		break;

		case ESlateVisibility::Collapsed:
			OfflineList->SetVisibility(ESlateVisibility::Visible);
		break;
	}

}
