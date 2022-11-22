// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendProfileTooltip.h"
#include "../Structs/FriendData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UFriendProfileTooltip::UpdateTooltipData_Implementation(UFriendData* friendProfile)
{
	if (friendProfile != nullptr)
	{
		auto pStatus = friendProfile->ProfileStatus;

		if (AvatarPic)
			AvatarPic->SetBrushFromTexture(pStatus.AvatarImage);

		if (NickName)
			NickName->SetText(FText::FromString(pStatus.NickName));

		if (FullName)
			FullName->SetText(FText::FromName(pStatus.FullName));

		if (ConnectStatus)
		{

			ConnectStatus->SetText(pStatus.bIsConnected ?
								   FText::FromString("Online") :
								   FText::FromString("Offline"));

			ConnectStatus->SetColorAndOpacity(FSlateColor(pStatus.bIsConnected ?
														  FLinearColor::Green :
														  FLinearColor::Red));
		}

		if (Level)
			Level->SetText(FText::FromString(
				FString::Printf(TEXT("Level %d"), pStatus.Level)));

		if (LastGame)
			LastGame->SetText(FText::FromString(pStatus.LastGamePlayed));
	}
}
