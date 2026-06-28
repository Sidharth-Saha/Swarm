// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SwarmPawn.h"

#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASwarmPawn::ASwarmPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Setup root component
	RootComponent = CreateDefaultSubobject<USphereComponent>("RootComponent");
	
	// Initialize mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	// Initialize camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	CameraBoom->SetupAttachment(RootComponent);
	
	// Initialize camera
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>("TopDownCamera");
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ASwarmPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASwarmPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASwarmPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

