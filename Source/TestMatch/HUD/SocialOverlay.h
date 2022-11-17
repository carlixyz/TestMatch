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
	class APlayerController* OwningPlayer;

public:
	virtual void NativeConstruct() override;

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


	UFUNCTION()
	void InitDataLists();

	UFUNCTION()
	void UpdateWidgets(FString text);
	
	UFUNCTION()
	void SetDisplayText(FString textToDisplay);

private:

	void UpdateOnlineList();

	void UpdateOfflineList();

	void SetFriendOnline(UObject* friendItem);

	void SetFriendOffline(UObject* friendItem);

	UFUNCTION()
	void ToggleOnlineListVisibility();

	UFUNCTION()
	void ToggleOfflineListVisibility();

};
