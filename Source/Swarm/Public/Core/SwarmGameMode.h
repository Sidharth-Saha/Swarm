		// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SwarmGameMode.generated.h"

class AEnemyBase;

/**
 * 
 */
UCLASS()
class SWARM_API ASwarmGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASwarmGameMode();
	
	void OnPlayerDeath();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyBase> GruntClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyBase> RunnerClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyBase> BruteClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemies", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyBase> ShooterClass;
	
	float SpawnInterval = 2.0f;
	
	float SpawnRadius = 2000.0f;
	
	FTimerHandle SpawnTimerHandle;
	
	void SpawnEnemy();
};
