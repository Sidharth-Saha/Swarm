// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MainMenuPlayerController.h"

#include "UI/MainMenuWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ensureMsgf(MenuWidgetClass, TEXT("MenuWidgetClass not set on %s"), *GetName()))
	{
		MenuWidget = CreateWidget<UMainMenuWidget>(this, MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());
			SetInputMode(InputMode);
		}
		
		bShowMouseCursor = true;
	}
}
