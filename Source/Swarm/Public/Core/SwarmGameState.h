// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/GameStateBase.h"
#include "SwarmGameState.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8 
{
	MainMenu,
	Playing,
	GameOver
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGameState, NewState);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameScoreChanged, int32, NewScore, int32, Delta);

/**
 * 
 */
UCLASS()
class SWARM_API ASwarmGameState : public AGameStateBase
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game State", meta = (AllowPrivateAccess = "true"))
	EGameState GameState = EGameState::MainMenu;
	
	int32 GameScore = 0;
	
public:
	void SetGameState(EGameState NewState);
	UFUNCTION(BlueprintCallable)
	EGameState GetGameState() const { return GameState; }
	
	UPROPERTY(BlueprintAssignable, Category = "Game State")
	FOnGameStateChanged OnGameStateChanged;
	
	UFUNCTION(BlueprintPure, Category = "Game Score")
	int32 GetGameScore() const { return GameScore; }
	
	UFUNCTION(BlueprintCallable, Category = "Game Score")
	void AddScore(int32 Amount);
	
	UPROPERTY(BlueprintAssignable, Category = "Game Score")
	FOnGameScoreChanged OnGameScoreChanged;
};
