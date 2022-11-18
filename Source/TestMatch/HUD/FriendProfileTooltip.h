// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FriendProfileTooltip.generated.h"

/**
 * 
 */
UCLASS()
class TESTMATCH_API UFriendProfileTooltip : public UUserWidget
{
	GENERATED_BODY()
protected:
	/// Player Avatar Icon ------------------
	UPROPERTY(meta = (BindWidget))
	class UImage* AvatarPic;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NickName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FullName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ConnectStatus;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Level;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LastGame;

public:
	UFUNCTION(BlueprintCallable)
	UFriendProfileTooltip* ReturnTooltip();

	UFUNCTION(BlueprintCallable)
	void UpdateTooltipData(class UFriendData* friendProfile);
};
