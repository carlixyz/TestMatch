// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToastPopup.generated.h"

/**
 * 
 */
UCLASS()
class TESTMATCH_API UToastPopup : public UUserWidget
{
	GENERATED_BODY()

	// These must be the name for Reveal popup Window
	UPROPERTY( Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* RevealWindow;

	// These must be the name for Hid popup Window
	UPROPERTY( Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideWindow;

	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* AnnounceText;

	FTimerHandle DisplayTimer;

	void GoodBye();

public:
	UFUNCTION(BlueprintNativeEvent)
	void SetupDisplayedName(const FString& nameToDisplay);

	UFUNCTION(BlueprintCallable)
	void LaunchDelayToHide();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DisplayDelay = 10.0f;
};
