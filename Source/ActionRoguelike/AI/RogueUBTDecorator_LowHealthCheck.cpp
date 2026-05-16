// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueUBTDecorator_LowHealthCheck.h"

#include "AIController.h"
#include "SharedGameplayTags.h"
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
		//is low health?
		
		float HealthFraction = ActionComp->GetAttributeValue(SharedGameplayTags::Attribute_Health) / 
			ActionComp->GetAttributeValue(SharedGameplayTags::Attribute_HealthMax);
		
		return HealthFraction < LowHealthPercentage;
	}
	
	return false;
}
