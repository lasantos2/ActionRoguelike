// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RogueCoinPickUpSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueCoinPickUpSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
	// Stucts of arrays or arrays of structs.
	
protected:
	TArray<FVector> CoinLocations;
	TArray<int32> CoinAmounts;
	TArray<FPrimitiveInstanceId> MeshIDs;
	
	virtual void Tick(float DeltaTime) override;
	
	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(RogueCoinPickUpSubsystem , STATGROUP_Tickables);
	};
	
	UPROPERTY()
	TObjectPtr<UInstancedStaticMeshComponent> WorldISM;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> WorldAudioComp;
	
	void OnPickupMeshLoadComplete(const FSoftObjectPath& PickupMeshPath, UObject* LoadedObject);
	
	void OnPickupSoundLoadComplete(const FSoftObjectPath& PickupSoundPath, UObject* LoadedObject);
	
	void PlayPickupSound();
	
	/* Cached Param from developer settins for audio comp pickups  */
	FName CoinPickupTriggerParamName;
	
	
public:
	
	void AddCoinPickups(TArray<FVector> NewLocations, TArray<int32> NewAmounts);
	
	void RemoveCoinPickup(int32 IndexToRemove);
	
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
};
