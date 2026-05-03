// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAICharacter.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
ARogueAICharacter::ARogueAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ActionSystemComponent = CreateDefaultSubobject<URogueActionSystemComponent>(TEXT("ActionSystemComp"));

}

float ARogueAICharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamange =  Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ActionSystemComponent->ApplyHealthChange(-DamageAmount);
	
	return ActualDamange;
	
}

void ARogueAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	ActionSystemComponent->OnHealthChanged.AddDynamic(this, &ARogueAICharacter::OnHealthChanged);
}

void ARogueAICharacter::OnHealthChanged(float NewHealth, float OldHealth)
{
	if (FMath::IsNearlyZero(NewHealth))
	{
		DisableInput(nullptr);
		GetMovementComponent()->StopMovementImmediately();
		PlayAnimMontage(DeathMontage);
	}

}


