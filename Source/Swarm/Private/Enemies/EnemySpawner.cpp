// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemySpawner.h"

#include "Enemies/EnemyBase.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	ensureMsgf(GruntClass, TEXT("GruntClass not set on %s"), *GetName());
	ensureMsgf(RunnerClass, TEXT("RunnerClass not set on %s"), *GetName());
	ensureMsgf(BruteClass, TEXT("BruteClass not set on %s"), *GetName());
	ensureMsgf(ShooterClass, TEXT("ShooterClass not set on %s"), *GetName());
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

