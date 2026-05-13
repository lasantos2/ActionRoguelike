// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction.h"
#include "RogueActionSystemComponent.h"

void URogueAction::StartAction_Implementation()
{
	bIsRunning = true;
	float GameTime = GetWorld()->GetTimeSeconds();
	
	UE_LOGFMT(LogTemp, Log, "Started Action {ActionName} - {WorldTime}", 
		("ActionName",ActionName.ToString()), 
		("WorldTime", GameTime));
	
	GetOwningComponent()->ActiveGameplayTags.AppendTags(GrantTags);
	
	// consumre required resources
	for (TPair<FGameplayTag, float> Cost: ActivationCost)
	{
		GetOwningComponent()->ApplyAttributeChange(Cost.Key, -Cost.Value, Modifier);
	}
}

void URogueAction::StopAction_Implementation()
{
	
	bIsRunning = false;
	float GameTime = GetWorld()->GetTimeSeconds();
	
	UE_LOGFMT(LogTemp, Log, "Stopped Action {ActionName} - {WorldTime}", 
		("ActionName",ActionName.ToString()), 
		("WorldTime", GameTime));
	
	CooldownUntil = GetWorld()->TimeSeconds + CooldownTime;
	
	GetOwningComponent()->ActiveGameplayTags.RemoveTags(GrantTags);
}

bool URogueAction::CanStart() const
{
	if (IsRunning())
	{
		return false;
	}
	if (GetCooldownTimeRemaining() > 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("Cooldown remaining: %f"), GetCooldownTimeRemaining());
		return false;
	}
	
	URogueActionSystemComponent* OwningComp = GetOwningComponent();
	
	if (OwningComp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	
	for (TPair<FGameplayTag, float> Cost: ActivationCost)
	{
		float AvailableAttributeAmout = OwningComp->GetAttributeValue(Cost.Key);
		if (AvailableAttributeAmout < Cost.Value)
		{
			UE_LOGFMT(LogTemp, Log, "Not enought {AttributeName} to activate {ActionName}. "
				"Have {AvailableAttributeValue} amd meed {RequiredAttributeValue} ",
				("AttributeName", Cost.Key.ToString()),
				("ActionName", ActionName.ToString()),
				("AvailableAttributeValue",AvailableAttributeAmout),
				("RequiredAttributeValue", Cost.Value));
			
		return false;
		}
	}
	
	return true;
}

URogueActionSystemComponent* URogueAction::GetOwningComponent() const
{
	return Cast<URogueActionSystemComponent>(GetOuter());
}
