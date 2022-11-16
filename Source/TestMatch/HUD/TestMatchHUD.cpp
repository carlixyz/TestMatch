// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMatchHUD.h"
#include "GameFramework/PlayerController.h"
#include "SocialOverlay.h"

void ATestMatchHUD::BeginPlay()
{
	Super::BeginPlay();
	AddControllerOverlay();
}


void ATestMatchHUD::AddControllerOverlay()
{

	APlayerController* playerController = GetOwningPlayerController();
	if (playerController && ControllerOverlayClass)
	{
		ControllerOverlay = CreateWidget<USocialOverlay>(playerController, ControllerOverlayClass);
		ControllerOverlay->AddToViewport();
	}
}

//void ATestMatchHUD::DrawHUD()
//{
//
//}