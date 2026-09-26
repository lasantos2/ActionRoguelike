#pragma once
#include "RogueGameTypes.generated.h"
#define COLLISION_INTERACTION ECC_GameTraceChannel1
#define ROGUE_PLAYER ECC_GameTraceChannel2
#define ROGUE_PROJECTILE ECC_GameTraceChannel3
#define ROGUE_PICKUP ECC_GameTraceChannel4
#define NAME_TargetActor "TargetActor"


class URogueMonsterData;
class ARogueAICharacter;
class UEnvQuery;
class UDataTable;


USTRUCT(BlueprintType)
struct FMonsterSpawnData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FMonsterSpawnData():SpawnCost(0.0f){};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<URogueMonsterData> MonsterData;
	
	/* Points required by gamemode to spawn this unit */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnCost;

	UPROPERTY(EditAnywhere)
	float SpawnWeight = 1.0f;
};

USTRUCT(BlueprintType)
struct FRogueDirectorData
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn System")
	TObjectPtr<UEnvQuery> SpawnLocationQuery;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn System")
	TObjectPtr<UDataTable> MonsterSpawnTable;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn System")
	FRuntimeFloatCurve CreditGainCurve;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn System")
	float TickInterval = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawn System")
	float TimeBetweenWaves = 6.0f;
	
	float CurrentCredits = 0.0f;
	
	float NextTickTime = 0.0f;
	
	FRandomStream Randomstream_MonsterSelection;
	
};
