// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "FriendListEntry.generated.h"

/**
 * UCLASS(Abstract)
 */
UCLASS()
class TESTMATCH_API UFriendListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
protected:
	/// Initialize Class to enable IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* listItemObject) override;

	// Extend your custom implementation by BluPrint here
	UFUNCTION(BlueprintNativeEvent)
	void SetupWidgetOffline();

	// Extend your custom implementation by BluPrint here
	UFUNCTION(BlueprintNativeEvent)
	void SetupWidgetOnline();

	// Our current tooltip widget class, change it from here
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UFriendProfileTooltip> TooltipUIClass;

	// Our current tooltip widget, peek instance from here
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFriendProfileTooltip* ProfileTooltip;

	void CreateTooltipWidget(class UFriendData* friendData);

	/// Player Avatar Icon ------------------
	UPROPERTY(meta = (BindWidgetOptional))
	class UImage* AvatarImage;

	/// Player NickName ---------------------
	UPROPERTY(meta = (BindWidgetOptional))
	class UTextBlock* NickNameText;

	/// Player Connection Status 
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Connection;

	// Displayed Text Color When online
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OnlineColorFont;

	// Displayed Text Color When offline
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OfflineColorFont;


	/// Back of the panel color -----------
	UPROPERTY(meta = (BindWidgetOptional))
	class UBorder* BorderBG;

	// Displayed Color When enabled
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OnlineColorBG;

	// Displayed Color When player is offline
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OfflineColorBG;


};
