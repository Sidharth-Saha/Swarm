// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SwarmGameMode.h"

#include "Core/SwarmGameState.h"

void ASwarmGameMode::OnPlayerDeath()
{
	if (ASwarmGameState* SwarmGameState = GetGameState<ASwarmGameState>())
	{
		SwarmGameState->SetGameState(EGameState::GameOver);
	}
}
