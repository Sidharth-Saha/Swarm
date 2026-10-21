// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SWARM_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
	
private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> StartButton;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
	TObjectPtr<UButton> QuitButton;
	
	UPROPERTY(EditDefaultsOnly, Category = "Levels")
	TSoftObjectPtr<UWorld> ArenaLevel;
	
	UFUNCTION()
	void HandleStartClicked();
	
	UFUNCTION()
	void HandleQuitClicked();
};
