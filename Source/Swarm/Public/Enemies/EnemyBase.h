// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyBase.generated.h"

UCLASS()
class SWARM_API AEnemyBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> CollisionBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UFloatingPawnMovement> MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 500.0f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UHealthComponent> HealthComponent;
	
	// Damage the enemy does to the player
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 10.0f;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
protected:
	virtual void TickBehavior(float DeltaTime);
	
	UFUNCTION()
	void HandleDeath(AActor* DeadActor, AActor* Killer);
};
