// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueUBTDecorator_LowHealthCheck.h"

#include "AIController.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

bool URogueUBTDecorator_LowHealthCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	
	check(Pawn);
	
	URogueActionSystemComponent* ActionComp = Pawn->GetComponentByClass<URogueActionSystemComponent>();
	
	if (ensure(ActionComp))
	{
	check(false);
		//is low health?
		//return (ActionComp->GetAttributeHealth() / ActionComp->GetAttributeHealthMax()) < LowHealthPercentage;
	}
	return false;
}
