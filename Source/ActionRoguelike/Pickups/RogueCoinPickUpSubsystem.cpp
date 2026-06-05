// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueCoinPickUpSubsystem.h"

#include "ActionRoguelike.h"
#include "EngineUtils.h"
#include "Components/AudioComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Core/RogueDeveloperSettings.h"
#include "Player/RoguePlayerCharacter.h"
#include "ProfilingDebugging/CountersTrace.h"


TRACE_DECLARE_INT_COUNTER(CoinInstanceCount, TEXT("Coins In World"))

class ARoguePlayerCharacter;

void URogueCoinPickUpSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSubsystem::Tick)
	
	UWorld* World = GetWorld();
	
	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	for (ARoguePlayerCharacter* PlayerCharacter : TActorRange<ARoguePlayerCharacter>(World))
	{
		PlayerLocation = PlayerCharacter->GetActorLocation();
	}
	
	const float PickupRadius = 200.f;

	TArray<int32> ProcessList;
	
	{
		TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSubsystem::Tick::DistanceCheck)
		for (int i = 0; i < CoinLocations.Num(); ++i)
		{
			float DistPlayerToCoin = FVector::Dist(PlayerLocation, CoinLocations[i]);
			if (DistPlayerToCoin < PickupRadius)
			{
				ProcessList.Add(i);
			}
		}
	}
	

	int32 TotalCoinsToGrant = 0;


	{
		
		TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSubsystem::Tick::ProcessList)
		for (int i = ProcessList.Num()-1; i >= 0; --i)
		{
			int32 CoinIndex = ProcessList[i];
			TotalCoinsToGrant += CoinAmounts[CoinIndex];
		
			RemoveCoinPickup(CoinIndex);
		}
	}
	
	if (TotalCoinsToGrant > 0)
		PlayPickupSound();

#if 0
	{
		UE_CLOG(TotalCoinsToGrant>0,LogGame, Log, TEXT("Coin Amount = %d"), TotalCoinsToGrant);
	
		for (int i = 0; i < CoinLocations.Num(); i++)
		{
			DrawDebugPoint(World, CoinLocations[i], 8.0f, FColor::White);
		}
	}
#endif
}

void URogueCoinPickUpSubsystem::OnPickupMeshLoadComplete(const FSoftObjectPath& PickupMeshPath, UObject* LoadedObject)
{
	
	WorldISM->SetStaticMesh(Cast<UStaticMesh>(LoadedObject));
	
}

void URogueCoinPickUpSubsystem::OnPickupSoundLoadComplete(const FSoftObjectPath& PickupSoundPath, UObject* LoadedObject)
{
	WorldAudioComp->SetSound(Cast<USoundBase>(LoadedObject));
}

void URogueCoinPickUpSubsystem::PlayPickupSound()
{
	if (!WorldAudioComp->IsPlaying())
	{
		WorldAudioComp->Play();
	}
	
	const URogueDeveloperSettings* DevSettings = GetDefault<URogueDeveloperSettings>();
	WorldAudioComp->SetTriggerParameter(CoinPickupTriggerParamName);
}

void URogueCoinPickUpSubsystem::AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSystem::AddCoinPickups);

	CoinLocations.Append(NewLocations);
	CoinAmounts.Append(NewAmounts);
	
	TArray<FTransform> MeshTransforms;
	for (int i = 0; i < NewLocations.Num(); ++i)
	{
		MeshTransforms.Add(FTransform(NewLocations[i] + FVector(0,0,100)));
	}
	
	TArray<FPrimitiveInstanceId> NewMeshIDs = WorldISM->AddInstancesById(MeshTransforms, true, false);
	MeshIDs.Append(NewMeshIDs);
	TRACE_COUNTER_SET(CoinInstanceCount, CoinLocations.Num());
}

void URogueCoinPickUpSubsystem::RemoveCoinPickup(int32 IndexToRemove)
{
	
	TRACE_CPUPROFILER_EVENT_SCOPE(CoinPickupSystem::RemoveCoinPickup);
	CoinLocations.RemoveAt(IndexToRemove);
	CoinAmounts.RemoveAt(IndexToRemove);
	
	WorldISM->RemoveInstanceById(MeshIDs[IndexToRemove]);
	MeshIDs.RemoveAt(IndexToRemove);
	
	TRACE_COUNTER_SET(CoinInstanceCount, CoinLocations.Num());
}

void URogueCoinPickUpSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
	WorldISM = NewObject<UInstancedStaticMeshComponent>(&InWorld, NAME_None, RF_Transient);
	WorldISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WorldISM->SetAffectDistanceFieldLighting(false);
	WorldISM->RegisterComponentWithWorld(&InWorld);
	
	TRACE_COUNTER_SET(CoinInstanceCount, 0)
	
	FLoadSoftObjectPathAsyncDelegate Delegate;
	FLoadSoftObjectPathAsyncDelegate DelegateSound;
	Delegate.BindUObject(this, &ThisClass::OnPickupMeshLoadComplete);
	DelegateSound.BindUObject(this, &ThisClass::OnPickupSoundLoadComplete);
	
	const URogueDeveloperSettings* DevSettings = GetDefault<URogueDeveloperSettings>();
	CoinPickupTriggerParamName = DevSettings->CointPickupTriggerParameter;
	int32 OwO = DevSettings->CoinPickupMesh.LoadAsync(Delegate);
	int32 OwOSound = DevSettings->CoinPickupSound.LoadAsync(DelegateSound);
	WorldAudioComp = NewObject<UAudioComponent>(&InWorld, NAME_None, RF_Transient);
	WorldAudioComp->SetAutoActivate(false);
	WorldAudioComp->RegisterComponentWithWorld(&InWorld);
}
