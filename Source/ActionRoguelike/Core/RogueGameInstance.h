// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RogueGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	// Game Instance used for things that survive beyond the level
	// Weakobject not a strong ref so not hold on memory. Could contain nullptrs, GC deletes monsters
public:
	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<APawn>> AliveMonsters;
	
	
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
};
