// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RogueGameMode.h"
#include "RoguePrimaryGameMode.generated.h"

struct FRogueDirectorData;
struct FMonsterSpawnData;
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
	
	UPROPERTY(EditDefaultsOnly, Category="Spawn Systems")
	TArray<FRogueDirectorData> Directors;
	
	UPROPERTY(EditDefaultsOnly, Category="Spawn Systems")
	int32 GlobalStartingSeed = 0;

	void SpawnQueryCompleted(TSharedPtr<FEnvQueryResult> QueryResult, FMonsterSpawnData* SelectedMonster);
	
	void OnMonsterClassLoaded(const FSoftObjectPath& LoadedObjectPath, UObject* LoadedObject, FVector SpawnLocation, FMonsterSpawnData* SelectedMonster);
	
	bool TrySpawnMonster(FRogueDirectorData& Director);
	
public:
	ARoguePrimaryGameMode();
	
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void StartPlay() override;
};
