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

	UPROPERTY(EditAnywhere, Category = "Player Status")
	TSubclassOf<class UUserWidget> FriendOnlineEntryClass;

	UPROPERTY(EditAnywhere, Category = "Player Status")
	TSubclassOf<class UUserWidget> FriendOfflineEntryClass;

	UFUNCTION()
	void UpdateWidgets(FString text);

	void SetDisplayText(FString textToDisplay);

private:


	void UpdateOnlineList();

	void UpdateOfflineList();

	void SetFriendOnline(UObject* friendItem);

	void SetFriendOffline(UObject* friendItem);

};
