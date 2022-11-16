// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Structs/FriendStatus.h"
#include "SocialComponent.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnDataUpdate, FString, textData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTMATCH_API USocialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USocialComponent();

	/// Get's called everytime Services Get a change in our friends Status
	UFUNCTION()
	void OnDataChanged(TArray<FFriendStatus>& friendStats);

	/// Calls all the Widgets to update Info
	UPROPERTY()
	FOnDataUpdate NotifyDataUpdate;

protected:
	virtual void BeginPlay() override;

private:

	/// Friend List Local copy Handling Here
	//TArray<FFriendStatus> FriendProfiles;

	UPROPERTY(VisibleAnywhere)
	TArray<class UFriendData*> FriendDataProfiles;

};
