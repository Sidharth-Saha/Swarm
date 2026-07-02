// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SwarmPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASwarmPawn::ASwarmPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialize root component
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	
	// Initialize mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	
	// Initialize camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	CameraBoom->SetupAttachment(RootComponent);
	
	// Initialize camera
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	// Initialize movement component
	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
}

// Called when the game starts or when spawned
void ASwarmPawn::BeginPlay()
{
	Super::BeginPlay();
	
	// Setup input context mapping
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			if (ensure(DefaultMappingContext))
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

// Called every frame
void ASwarmPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Update aim direction for mouse input
	UpdateMouseAim();
}

// Called to bind functionality to input
void ASwarmPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Bind input actions
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASwarmPawn::Move);
		EIC->BindAction(AimAction, ETriggerEvent::Triggered, this, &ASwarmPawn::Aim);
		EIC->BindAction(FireAction, ETriggerEvent::Started, this, &ASwarmPawn::StartFire);
	}
}

void ASwarmPawn::Move(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	
	AddMovementInput(FVector::ForwardVector, Input.X);
	AddMovementInput(FVector::RightVector, Input.Y);
}

void ASwarmPawn::Aim(const FInputActionValue& Value)
{
	const FVector2D Input = Value.Get<FVector2D>();
	
	// if input exceeds deadzone update aim direction
	if (Input.SizeSquared() > FMath::Square(AimDeadzone))
	{
		AimDirection = FVector(Input.X, Input.Y, 0.0f).GetSafeNormal();
	}
}

void ASwarmPawn::StartFire(const FInputActionValue& Value)
{
	const bool bPressed = Value.Get<bool>();
	
	// TODO be implemented
}

void ASwarmPawn::UpdateMouseAim()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		FHitResult Hit;
		if (PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			const FVector ToCursor = Hit.Location - GetActorLocation();
			const FVector Flat = FVector(ToCursor.X, ToCursor.Y, 0.0f);
			if (!Flat.IsNearlyZero())
			{
				AimDirection = Flat.GetSafeNormal();
			}
		}
	}
}
