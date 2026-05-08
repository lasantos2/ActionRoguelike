// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionSystemComponent.h"
#include "RogueAction.h"


URogueActionSystemComponent::URogueActionSystemComponent()
{
	bWantsInitializeComponent = true;
}

void URogueActionSystemComponent::InitializeComponent()
{
	Super::InitializeComponent();



	for (TSubclassOf<URogueAction> ActionClass : DefaultActions)
	{
		if (ensure(ActionClass))
		{
			GrantAction(ActionClass);
		}
	}

}

void URogueActionSystemComponent::StartAction(FName InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			if (Action->CanStart())
			{
				Action->StartAction();
			}
			
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No Action found with name %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::StopAction(FName InActionName)
{
	for (URogueAction* Action : Actions)
	{
		if (Action->GetActionName() == InActionName)
		{
			Action->StopAction();
			return;
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("No Action found with name %s"), *InActionName.ToString());
}

void URogueActionSystemComponent::ApplyHealthChange(float InValueChange)
{
	float OldHealth = Attributes.Health;
	Attributes.Health += InValueChange;
	
	// Get defaults lets us get the default value of the attribute as set in the class. Very nice saves a variable name
	float MaxHealth = Attributes.HealthMax;
	
	Attributes.Health = FMath::Clamp(Attributes.Health + InValueChange, 0.0f, MaxHealth);
	
	if (!FMath::IsNearlyEqual(OldHealth, Attributes.Health))
	{
		OnHealthChanged.Broadcast(Attributes.Health, OldHealth);
	}
	
	UE_LOG(LogTemp, Log, TEXT("New Health: %f, Max Health: %f"), Attributes.Health, MaxHealth);
	
}

float URogueActionSystemComponent::GetAttributeHealthMax()
{return Attributes.HealthMax;}

bool URogueActionSystemComponent::IsFullHeath()
{
	return Attributes.Health == Attributes.HealthMax;
}

void URogueActionSystemComponent::GrantAction(TSubclassOf<URogueAction> NewActionClass)
{
	
	URogueAction* NewAction = NewObject<URogueAction>(this, NewActionClass);
	Actions.Add(NewAction);
}
