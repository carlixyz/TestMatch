// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Structs/FriendStatus.h"
#include "SocialComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDataSync, FString, textData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTMATCH_API USocialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USocialComponent();

	UFUNCTION()
	TArray<class UFriendData*> GetInitialFriendData();

	/// Get's called everytime Services Get a change in our friends Status
	UFUNCTION()
	void SyncData(TArray<FFriendStatus>& friendStats);

	/// Notify all  Widgets to update Info
	UPROPERTY()
	FOnDataSync NotifyDataSync;

protected:
	virtual void BeginPlay() override;

private:

	/// Friend List Local copy Handling Here
	UPROPERTY(VisibleAnywhere)
	TArray<UFriendData*> FriendDataProfiles;

};
