// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TestMatchHUD.generated.h"

/**
 * 
 */
UCLASS()
class TESTMATCH_API ATestMatchHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<class UUserWidget> ControllerOverlayClass;

	// We always use these TSubclasses for Instance Creation (check on AddControllerOverlay())
	class USocialOverlay* ControllerOverlay;
	
protected:
	virtual void BeginPlay() override;
	void AddControllerOverlay();

private:
	UPROPERTY()
	class APlayerController* OwningPlayer;
};
