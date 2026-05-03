// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RogueUBTDecorator_LowHealthCheck.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueUBTDecorator_LowHealthCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Category = AI)
	bool PerformConditionCheckAI(AAIController* OwnerController, APawn* ControlledPawn);
	
	UPROPERTY(EditAnywhere, Category = "AI")
	float LowHealthPercentage = .3f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
	FBlackboardKeySelector IsBelowHealthKey;
	
	
};
