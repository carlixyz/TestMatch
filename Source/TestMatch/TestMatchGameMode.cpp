// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestMatchGameMode.h"
#include "TestMatchPlayerController.h"
#include "TestMatchCharacter.h"
#include "Components/ServicesComponent.h"
#include "UObject/ConstructorHelpers.h"

ATestMatchGameMode::ATestMatchGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATestMatchPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
/// C: / UnrealProjects / GlobantExercise / TestMatch / Content / Blueprints / BP_TopDownCharacter.uasset
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	Services = CreateDefaultSubobject<UServicesComponent>(TEXT("Services"));

}