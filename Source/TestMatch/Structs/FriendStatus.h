// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"	
#include "Engine/DataTable.h"
#include "FriendStatus.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct TESTMATCH_API FFriendStatus : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* AvatarImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NickName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConnected = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName FullName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LastGamePlayed;
};

