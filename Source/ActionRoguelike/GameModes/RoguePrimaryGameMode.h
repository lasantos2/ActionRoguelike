// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RogueGameMode.h"
#include "RoguePrimaryGameMode.generated.h"

class UEnvQuery;
struct FEnvQueryResult;
/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ARoguePrimaryGameMode : public ARogueGameMode
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn System")
	TObjectPtr<UEnvQuery> SpawnLocationQuery;
	
	void SpawnQueryCompleted(TSharedPtr<FEnvQueryResult> QueryResult);
	
public:
	ARoguePrimaryGameMode();
	
	virtual void Tick(float DeltaSeconds) override;
	
};
