// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SwarmPlayerController.h"

void ASwarmPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	bShowMouseCursor = true;
	
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	SetInputMode(InputMode);
}
