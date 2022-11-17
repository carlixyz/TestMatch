// Fill out your copyright notice in the Description page of Project Settings.

#include "FriendListEntry.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "../Structs/FriendData.h"
#include "../Structs/FriendStatus.h"

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
			AvatarImage->SetBrushTintColor(FSlateColor(FLinearColor::White));
			NickNameText->SetColorAndOpacity(FSlateColor(OnlineColorFont));

			Connection->SetText(FText::FromString("Online"));
			Connection->SetColorAndOpacity(FSlateColor(OnlineColorFont));

			BorderBG->SetBrushColor(OnlineColorBG);
		}
		else
		{
			AvatarImage->SetBrushTintColor(OfflineColorBG);
			NickNameText->SetColorAndOpacity(FSlateColor(OfflineColorFont));

			Connection->SetText(FText::FromString("Offline"));
			Connection->SetColorAndOpacity(FSlateColor(OfflineColorFont));

			BorderBG->SetBrushColor( OfflineColorBG );
		}
	}
}

