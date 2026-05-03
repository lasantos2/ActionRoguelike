// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RogueBTService_CheckRangeTo.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueBTService_CheckRangeTo : public UBTService
{
	GENERATED_BODY()
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
	FBlackboardKeySelector TargetActorKey;
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
	float MaxAttackRange = 500;
	
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AI")
	FBlackboardKeySelector WithinRangeKey;
	
	URogueBTService_CheckRangeTo();
	
};
