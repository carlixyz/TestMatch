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

	void SetupWidgetOffline();

	void SetupWidgetOnline();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UFriendProfileTooltip> TooltipUIClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFriendProfileTooltip* ProfileTooltip;

	void CreateTooltipWidget(class UFriendData* friendData);

	/// Player Avatar Icon ------------------
	UPROPERTY(meta = (BindWidget))
	class UImage* AvatarImage;

	/// Player NickName ---------------------
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NickNameText;

	/// Player Connection Status 
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Connection;

	// Displayed Text Color When online
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OnlineColorFont;

	// Displayed Text Color When offline
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OfflineColorFont;


	/// Back of the panel color -----------
	UPROPERTY(meta = (BindWidget))
	class UBorder* BorderBG;

	// Displayed Color When enabled
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OnlineColorBG;

	// Displayed Color When player is offline
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor OfflineColorBG;


};
