// Fill out your copyright notice in the Description page of Project Settings.


#include "ToastPopup.h"
#include "Components/TextBlock.h"
#include "TimerManager.h"


void UToastPopup::SetupDisplayedName_Implementation(const FString& nameToDisplay)
{
	if (RevealWindow)
		PlayAnimation(RevealWindow);

	if (AnnounceText)
		AnnounceText->SetText(FText::FromString(nameToDisplay));

	LaunchDelayToHide();

	if (HideWindow)
		PlayAnimation(HideWindow, .0f, 1, EUMGSequencePlayMode::Forward, .5f );
}

void UToastPopup::LaunchDelayToHide()
{
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
