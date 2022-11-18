// Fill out your copyright notice in the Description page of Project Settings.


#include "ToastPopup.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"


void UToastPopup::SetupDisplayedName(FString nameToDisplay)
{
	if (AnnounceText)
		AnnounceText->SetText(FText::FromString(nameToDisplay));


	/// We Show this info and after a while close it ...
	GetWorld()->GetTimerManager().SetTimer(DisplayTimer,
										   this,
										   &UToastPopup::GoodBye,
										   DisplayDelay,
										   false);
}

void UToastPopup::GoodBye()
{
	RemoveFromParent();
	//ConditionalBeginDestroy();
}

