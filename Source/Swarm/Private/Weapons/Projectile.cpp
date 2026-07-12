// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectile.h"

#include "Components/HealthComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Initialize root component
	RootComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	
	// Initialize the mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	// Initialize movement component
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->ProjectileGravityScale = 0.0f;
	MovementComponent->SetPlaneConstraintEnabled(true);
	MovementComponent->SetPlaneConstraintNormal(FVector::UpVector);
	MovementComponent->bSnapToPlaneAtStart = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Set initial speed
	MovementComponent->Velocity = GetActorForwardVector() * ProjectileSpeed;
	// Set life span
	SetLifeSpan(LifeSpan);
	
	// Bind collision function
	USphereComponent* SphereComponent = Cast<USphereComponent>(RootComponent);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnSphereOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor == this && OtherActor == GetInstigator())
	{
		if (UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>())
		{
			HealthComponent->ApplyDamage(Damage, GetInstigator());
		}
		
		Destroy();
	}
}
