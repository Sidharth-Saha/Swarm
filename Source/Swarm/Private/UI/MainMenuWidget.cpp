// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleStartClicked);
	QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::HandleQuitClicked);
}

void UMainMenuWidget::HandleStartClicked()
{
	if (ensureMsgf(!ArenaLevel.IsNull(), TEXT("ArenaLevel not set on %s"), *GetName()))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, ArenaLevel);
	}
}

void UMainMenuWidget::HandleQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}
