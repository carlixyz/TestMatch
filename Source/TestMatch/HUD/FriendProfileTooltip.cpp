// Fill out your copyright notice in the Description page of Project Settings.


#include "FriendProfileTooltip.h"
#include "../Structs/FriendData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

UFriendProfileTooltip* UFriendProfileTooltip::ReturnTooltip()
{
	return this;
}

void UFriendProfileTooltip::UpdateTooltipData(UFriendData* friendProfile)
{
	if (friendProfile != nullptr)
	{
		auto pStatus = friendProfile->ProfileStatus;

		AvatarPic->SetBrushFromTexture( pStatus.AvatarImage);

		NickName->SetText(FText::FromString( pStatus.NickName));

		FullName->SetText(FText::FromName( pStatus.FullName));

		ConnectStatus->SetText( pStatus.bIsConnected ?
							   FText::FromString("Online") :
							   FText::FromString("Offline") );

		ConnectStatus->SetColorAndOpacity( FSlateColor(pStatus.bIsConnected ?
													   FLinearColor::Green :
													   FLinearColor::Red ) );

		Level->SetText( FText::FromString( 
			FString::Printf( TEXT("Level %d"), pStatus.Level ) ));

		LastGame->SetText( FText::FromString(pStatus.LastGamePlayed));
	}
}
