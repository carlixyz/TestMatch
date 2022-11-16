// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FriendStatus.h"
#include "FriendData.generated.h"


/**
 * Wrapper Class for FriendStatus Struct 
 * Needed for ListView Component
 */
UCLASS(Blueprintable, BlueprintType)
class TESTMATCH_API UFriendData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Profile")
	FFriendStatus ProfileStatus;

	/// 

};
