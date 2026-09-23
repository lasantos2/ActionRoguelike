// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueActionEffect.h"
#include "ActionRoguelike.h"
#include "RogueActionSystemComponent.h"

void URogueActionEffect::ExecutePeriodicEffect_Implementation()
{
}

void URogueActionEffect::ResetDuration()
{
	GetWorld()->GetTimerManager().SetTimer(DurationHandle, this, &ThisClass::StopAction, Duration);
}

void URogueActionEffect::StartAction_Implementation()
{
	Super::StartAction_Implementation();
	
	if (Duration > 0.0f)
	{
		ResetDuration();
	}
	
	if (Period > 0.0f)
	{
		GetWorld()->GetTimerManager().SetTimer(PeriodHandle, this, &ThisClass::ExecutePeriodicEffect, Period, true);
		
	}
}

void URogueActionEffect::StopAction_Implementation()
{
	if (Period > 0.0f && GetWorld()->GetTimerManager().GetTimerRemaining(PeriodHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect();
	}
	Super::StopAction_Implementation();
	
	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeriodHandle);
	
	GetOwningComponent()->RemoveAction(this);
	
	
}

void URogueActionEffect::IncrementStackSize()
{
	StackCount++;
	if (bResetDurationStackIncreases)
	{
		ResetDuration();
	}
	
	UE_LOG(LogGame, Log, TEXT("Incremented %s, (%s) Stack to %d"), *GetName(), *GetNameSafe(GetOwningComponent()->GetOwner()),
		StackCount);
	
	
}
