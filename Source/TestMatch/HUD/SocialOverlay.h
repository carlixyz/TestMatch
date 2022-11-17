// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SocialOverlay.generated.h"

UCLASS()
class TESTMATCH_API USocialOverlay : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY()
	class ATestMatchPlayerController* OwningPlayer;

public:
	virtual void NativeOnInitialized() override; 	
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock* InfoText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UListView* OnlineList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* OfflineList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* ToggleOnlineButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton* ToggleOfflineButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UTextBlock* OnlineButtonText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UTextBlock* OfflineButtonText;

	UFUNCTION()
	void UpdateFriendWidgets(class UFriendData* friendsData);

private:

	UFUNCTION()
	void InitListViewData(TArray<UFriendData*> friendsDataList);

	void SetFriendItem( UFriendData* friendItem);

	UFUNCTION()
	void SetDisplayText(FString textToDisplay);

	UFUNCTION()
	void ToggleOnlineListVisibility();

	UFUNCTION()
	void ToggleOfflineListVisibility();

};
