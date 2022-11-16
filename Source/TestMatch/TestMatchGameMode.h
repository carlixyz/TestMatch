// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestMatchGameMode.generated.h"

UCLASS(minimalapi)
class ATestMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestMatchGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UServicesComponent* Services;

};



