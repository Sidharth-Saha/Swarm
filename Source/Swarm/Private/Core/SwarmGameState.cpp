// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/SwarmGameState.h"

void ASwarmGameState::SetGameState(EGameState NewState)
{
	if (NewState != GameState)
	{
		GameState = NewState;
		
		OnGameStateChanged.Broadcast(NewState);
	}
}

void ASwarmGameState::AddScore(int32 Amount)
{
	if (Amount > 0)
	{
		GameScore += Amount;
		OnGameScoreChanged.Broadcast(GameScore, Amount);
	}
}
