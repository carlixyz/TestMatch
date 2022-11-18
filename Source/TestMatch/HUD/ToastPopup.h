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
	
	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* AnnounceText;

	FTimerHandle DisplayTimer;

	void GoodBye();

public:
	UFUNCTION(BlueprintCallable)
	void SetupDisplayedName(FString nameToDisplay);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DisplayDelay = 10.0f;
};
