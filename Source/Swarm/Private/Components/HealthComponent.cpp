// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"

#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set current health to max health
	CurrentHealth = MaxHealth;
	
	// Set actor as alive
	bIsDead = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Check that max health is valid value
	if (!ensureMsgf(MaxHealth > 0.0f, TEXT("%s has MaxHealth <= 0 (%.1f); clamping to 1."), *GetOwner()->GetName(), MaxHealth))
	{
		MaxHealth = 1.0f;
	}
	// Set current health to max health
	CurrentHealth = MaxHealth;
	
	// Set actor as alive
	bIsDead = false;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthComponent::GetCurrentHealthPercent() const
{
	return MaxHealth > 0.0f ? CurrentHealth / MaxHealth : 0.0f;
}

bool UHealthComponent::IsDead() const
{
	return bIsDead;
}

void UHealthComponent::ApplyDamage(float Amount, AActor* DamageInstigator)
{
	if (!bIsDead && Amount > 0.0f)
	{
		const float OldHealth = CurrentHealth;
		CurrentHealth = FMath::Clamp(CurrentHealth - Amount, 0.0f, MaxHealth);
		const float Delta = CurrentHealth - OldHealth;
		
		OnHealthChanged.Broadcast(this, CurrentHealth, MaxHealth, Delta);
		
		if (CurrentHealth <= 0.0f)
		{
			bIsDead = true;
			OnDeath.Broadcast(GetOwner(), DamageInstigator);
		}
	}
}

void UHealthComponent::Heal(float Amount)
{
	if (!bIsDead && Amount > 0.0f)
	{
		const float OldHealth = CurrentHealth;
		CurrentHealth = FMath::Clamp(CurrentHealth + Amount, 0.0f, MaxHealth);
		const float Delta = CurrentHealth - OldHealth;
		
		if (Delta != 0.0f)
		{
			OnHealthChanged.Broadcast(this, CurrentHealth, MaxHealth, Delta);
		}
	}
}
