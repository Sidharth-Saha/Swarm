// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/SwarmGameMode.h"

#include "Core/SwarmGameState.h"
#include "Enemies/EnemyBase.h"
#include "Kismet/GameplayStatics.h"

ASwarmGameMode::ASwarmGameMode()
{
	GameStateClass = ASwarmGameState::StaticClass();
}

void ASwarmGameMode::OnPlayerDeath()
{
	if (ASwarmGameState* SwarmGameState = GetGameState<ASwarmGameState>())
	{
		SwarmGameState->SetGameState(EGameState::GameOver);
	}
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
}

void ASwarmGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	ensureMsgf(GruntClass, TEXT("GruntClass not set on %s"), *GetName());
	/*
	ensureMsgf(RunnerClass, TEXT("RunnerClass not set on %s"), *GetName());
	ensureMsgf(BruteClass, TEXT("BruteClass not set on %s"), *GetName());
	ensureMsgf(ShooterClass, TEXT("ShooterClass not set on %s"), *GetName());
	*/
	
	if (ASwarmGameState* SwarmGameState = GetGameState<ASwarmGameState>())
	{
		SwarmGameState->SetGameState(EGameState::Playing);
	}
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASwarmGameMode::SpawnEnemy, SpawnInterval, true);
	
	LiveEnemies.Reserve(MaxEnemies);
}

void ASwarmGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	
	Super::EndPlay(EndPlayReason);
}

void ASwarmGameMode::SpawnEnemy()
{
	const float Angle = FMath::RandRange(0.0f, 2.0f * PI);
	const FVector Offset(FMath::Cos(Angle) * SpawnRadius, FMath::Sin(Angle) * SpawnRadius, 0);

	if (APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		const FVector SpawnLocation = PlayerPawn->GetActorLocation() + Offset;
		
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (LiveEnemies.Num() < MaxEnemies)
		{
			if (AEnemyBase* Enemy = GetWorld()->SpawnActor<AEnemyBase>(GruntClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams))
			{
				LiveEnemies.Add(Enemy);
				Enemy->OnDestroyed.AddDynamic(this, &ASwarmGameMode::HandleEnemyDestroyed);
				/*
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Yellow,
						FString::Printf(TEXT("Alive enemies: %d"), LiveEnemies.Num()));
				}
				*/
			}
		}
	}
}

void ASwarmGameMode::HandleEnemyDestroyed(AActor* DestroyedActor)
{
	ensure(LiveEnemies.Num() > 0);
	AEnemyBase* Enemy = Cast<AEnemyBase>(DestroyedActor);
	if (ensure(Enemy))
	{
		LiveEnemies.RemoveSingleSwap(Enemy);
		if (Enemy->IsDead())
		{
			ASwarmGameState* SwarmGameState = GetGameState<ASwarmGameState>();
			if (ensure(SwarmGameState))
			{
				SwarmGameState->AddScore(Enemy->GetPoints());
			}
		}
	}
	/*
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Yellow,
			FString::Printf(TEXT("Alive enemies: %d"), LiveEnemies.Num()));
	}
	*/
}
