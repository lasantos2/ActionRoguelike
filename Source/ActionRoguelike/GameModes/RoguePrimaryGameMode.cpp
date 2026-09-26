// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePrimaryGameMode.h"

#include "ActionRoguelike.h"
#include "EngineUtils.h"
#include "RogueGameTypes.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "AI/RogueAICharacter.h"
#include "AI/RogueMonsterData.h"
#include "Core/RogueGameInstance.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"


ARoguePrimaryGameMode::ARoguePrimaryGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.1f;
}

void ARoguePrimaryGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float TotalElapsedTime = GetWorld()->TimeSeconds;
	
	const int32 MaxBotLimit = 5;
	URogueGameInstance* GI = GetGameInstance<URogueGameInstance>();
	if (GI->AliveMonsters.Num() >= MaxBotLimit)
	{
		UE_LOG(LogGameMode, Log, TEXT("Reached bot spawn limit of %d"), MaxBotLimit);
		return;
	}
	
	int32 KeyID = ONSCREENDEBUGKEY_SPAWNDIRECTORS;
	for (FRogueDirectorData& Director : Directors)
	{
		if (Director.MonsterSpawnTable == nullptr)
		{
			return;
		}
		
		float CreditsPerSecond = Director.CreditGainCurve.GetRichCurve()->Eval(TotalElapsedTime);
		Director.CurrentCredits += CreditsPerSecond * DeltaSeconds;
		
		FString DebugMesg = FString::Printf(TEXT("Current Credits : %f \nNext tick time: %f"), Director.CurrentCredits, Director.NextTickTime);
		GEngine->AddOnScreenDebugMessage(KeyID, PrimaryActorTick.TickInterval, FColor::Blue, DebugMesg);
		KeyID++;
		
		if (Director.NextTickTime > TotalElapsedTime)
		{
			continue;
		}
		
		bool bSuccess = TrySpawnMonster(Director);
		Director.NextTickTime = TotalElapsedTime + (bSuccess ? Director.TickInterval : Director.TimeBetweenWaves);
		
		//UE_LOG(LogGameMode, Log, TEXT("Total Credits: %f"), Director.CurrentCredits);
	}
}

void ARoguePrimaryGameMode::StartPlay()
{
	Super::StartPlay();
	
	FRandomStream GlobalStream = FRandomStream(GlobalStartingSeed);
	
	for ( FRogueDirectorData& Director: Directors)
	{
		int32 NewSeed = GlobalStream.RandRange(0, MAX_int32-1);
		Director.Randomstream_MonsterSelection = FRandomStream(NewSeed);
		
		UE_LOG(LogGameMode, Log, TEXT("Seed: %d"), Director.Randomstream_MonsterSelection.GetInitialSeed());
	}
}

void ARoguePrimaryGameMode::SpawnQueryCompleted(TSharedPtr<FEnvQueryResult> QueryResult, FMonsterSpawnData* SelectedMonster)
{
	//QueryResult->GetItemAsLocation(0);
	FVector SpawnLocation = QueryResult->GetItemAsLocation(0);
	
	SelectedMonster->MonsterData.LoadAsync(FLoadSoftObjectPathAsyncDelegate::CreateUObject(this, &ThisClass::OnMonsterClassLoaded, SpawnLocation, SelectedMonster));
	
}

void ARoguePrimaryGameMode::OnMonsterClassLoaded(const FSoftObjectPath& LoadedObjectPath, UObject* LoadedObject,
	FVector SpawnLocation, FMonsterSpawnData* SelectedMonster)
{
	
	FActorSpawnParameters SpawnParameters;
	FTransform SpawnTM=FTransform(SpawnLocation);
	URogueMonsterData* MonsterData = SelectedMonster->MonsterData.Get();
	
	ARogueAICharacter* NewMonster = GetWorld()->SpawnActorDeferred<ARogueAICharacter>(MonsterData->MonsterClass, FTransform::Identity);
	
	NewMonster->SetMonsterData(MonsterData);
	
	UGameplayStatics::FinishSpawningActor(NewMonster, SpawnTM);
	
	UE_VLOG_SPHERE(this, LogGameMode, Log, SpawnLocation, 32.0f, FColor::Blue, TEXT("MonsterType : %s \n Cost: %f"),
		*GetNameSafe(MonsterData->MonsterClass), *FString::SanitizeFloat(SelectedMonster->SpawnCost));
	
	URogueActionSystemComponent* ActionComp = NewMonster->GetActionSystemComponent();
	// set attributes, add buffs debuffs, etc.
	for (TSubclassOf<URogueAction> Action : MonsterData->Actions)
	{
		ActionComp->GrantAction(Action);
	}
}

bool ARoguePrimaryGameMode::TrySpawnMonster(FRogueDirectorData& Director)
{
	TArray<FMonsterSpawnData*> AllRows;
	Director.MonsterSpawnTable->GetAllRows("SelectMonster", AllRows);
	
	//int32 SelectedIndex = FMath::RandRange(0, AllRows.Num() - 1);
	//FMonsterSpawnData* SelectedRow = AllRows[SelectedIndex];

	float TotalWeights = 0.0f;
	for (FMonsterSpawnData* Row : AllRows)
	{
		TotalWeights += Row->SpawnWeight;
	}
	
	float SelectedWeight = Director.Randomstream_MonsterSelection.FRandRange(0.0f, TotalWeights);

	FMonsterSpawnData* SelectedRow = nullptr;
	TotalWeights = 0.0f;
	for (FMonsterSpawnData* Row : AllRows)
	{
		TotalWeights += Row->SpawnWeight;
		if (SelectedWeight <= TotalWeights)
		{
			SelectedRow = Row;
			break;
		}
	}
	
	if (Director.CurrentCredits < SelectedRow->SpawnCost)
	{
		UE_LOG(LogGameMode, Log, TEXT("Not enough credits to spawn monster %s"), *SelectedRow->MonsterData.GetAssetName())
		return false;
	}
	
	Director.CurrentCredits -= SelectedRow->SpawnCost;
	
	FQueryFinishedSignature CompleteDelegate = FQueryFinishedSignature::CreateUObject(this, &ThisClass::SpawnQueryCompleted, SelectedRow);
	
	FEnvQueryRequest Request(Director.SpawnLocationQuery, this);
	int32 QueryID = Request.Execute(EEnvQueryRunMode::SingleResult, CompleteDelegate);
	
	return QueryID != INDEX_NONE;
}


