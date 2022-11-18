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
	
	//UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	//class UTextBlock* InfoText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UListView* OnlineList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* OfflineList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UButton* ToggleOnlineButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UButton* ToggleOfflineButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UTextBlock* OnlineButtonText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	UTextBlock* OfflineButtonText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidgetOptional))
	class UVerticalBox* PopupArea;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UToastPopup> ToastPopupClass;

	UFUNCTION()
	void UpdateFriendWidgets(class UFriendData* friendsData);

private:

	void InitListViewData(TArray<UFriendData*> friendsDataList);

	void AnnounceFriendOnline(FString textToDisplay);

	UFUNCTION()
	void SetupFriendItem(UFriendData* friendItem);

	UFUNCTION()
	void ToggleOnlineListVisibility();

	UFUNCTION()
	void ToggleOfflineListVisibility();

};
