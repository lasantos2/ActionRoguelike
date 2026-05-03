// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueUBTDecorator_LowHealthCheck.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool URogueUBTDecorator_LowHealthCheck::PerformConditionCheckAI(AAIController* OwnerController, APawn* ControlledPawn)
{
	UBlackboardComponent* bbc = OwnerController->GetBlackboardComponent();
	
	return bbc->GetValueAsBool(IsBelowHealthKey.SelectedKeyName);
}
