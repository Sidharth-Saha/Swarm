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

APawn* ASwarmGameMode::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = GetInstigator();
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save default player pawns into a map
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	UClass* PawnClass = GetDefaultPawnClassForController(NewPlayer);
	APawn* ResultPawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo);
	if (!ResultPawn)
	{
		UE_LOGF(LogGameMode, Warning, "SpawnDefaultPawnAtTransform: Couldn't spawn Pawn of type %ls at %ls", *GetNameSafe(PawnClass), *SpawnTransform.ToHumanReadableString());
	}
	return ResultPawn;
}
