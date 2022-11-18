// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendListEntry.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "../Structs/FriendData.h"
#include "../Structs/FriendStatus.h"
#include "FriendProfileTooltip.h"
#include "Components/CanvasPanelSlot.h"

void UFriendListEntry::NativeOnListItemObjectSet(UObject* listItemObject)
{
	//OnlineColorBG = FLinearColor( .7f, .7f, .7f);
	//OfflineColorBG = FLinearColor::Gray;
	//OnlineColorFont = FLinearColor( .06f, .06f, .06f);
	//OfflineColorFont = FLinearColor( .45f, .45f, .45f);

	auto* itemData = Cast<UFriendData>(listItemObject);

	if (itemData)
	{
		AvatarImage->SetBrushFromTexture( itemData->ProfileStatus.AvatarImage);

		NickNameText->SetText(FText::FromString( itemData->ProfileStatus.NickName));

		if (itemData->ProfileStatus.bIsConnected)
		{
			// Set everything to enabled status
			SetupWidgetOnline();
		}
		else
		{
			// Set everything to disabled status
			SetupWidgetOffline();
		}

		CreateTooltipWidget(itemData);
	}
}

void UFriendListEntry::SetupWidgetOffline()
{
	AvatarImage->SetBrushTintColor(OfflineColorBG);
	NickNameText->SetColorAndOpacity(FSlateColor(OfflineColorFont));

	Connection->SetText(FText::FromString("Offline"));
	Connection->SetColorAndOpacity(FSlateColor(OfflineColorFont));

	BorderBG->SetBrushColor(OfflineColorBG);
}

void UFriendListEntry::SetupWidgetOnline()
{
	AvatarImage->SetBrushTintColor(FSlateColor(FLinearColor::White));
	NickNameText->SetColorAndOpacity(FSlateColor(OnlineColorFont));

	Connection->SetText(FText::FromString("Online"));
	Connection->SetColorAndOpacity(FSlateColor(OnlineColorFont));

	BorderBG->SetBrushColor(OnlineColorBG);
}


void UFriendListEntry::CreateTooltipWidget(UFriendData* friendData)
{
	if (TooltipUIClass != nullptr)
	{
		UFriendProfileTooltip* tooltipWidget = Cast<UFriendProfileTooltip>(CreateWidget(this, TooltipUIClass));

		if (tooltipWidget)
		{
			ProfileTooltip = tooltipWidget;
			SetToolTip(ProfileTooltip);
			ProfileTooltip->UpdateTooltipData(friendData);
		}
	}
	else
	{
		UE_LOG(LogTemp, 
			   Warning, 
			   TEXT("No Tooltip widget defined:\n Setup TooltipUIClass inside FriendListEntrty"));
	}
}

