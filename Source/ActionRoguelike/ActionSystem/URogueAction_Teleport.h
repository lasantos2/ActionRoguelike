// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueAction_ProjectileAttack.h"
#include "URogueAction_Teleport.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API UURogueAction_Teleport : public URogueAction_ProjectileAttack
{
	GENERATED_BODY()
	
	virtual void StartAction() override;
};
