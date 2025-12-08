// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueExplosiveBarrel.generated.h"


class UStaticMeshComponent;
class URadialForceComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundBase;
class UDamageType;
class UAudioComponenta;

UCLASS()
class ACTIONROGUELIKE_API ARogueExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARogueExplosiveBarrel();

	UPROPERTY(EditAnywhere, Category="Effects")
	float ExplosionDelayTime;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category="Effects")
	FName SocketName;

	UPROPERTY(EditAnywhere, Category="StaticMeshComp")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UPROPERTY(EditAnywhere, Category="Physics")
	TObjectPtr<URadialForceComponent> RadForce;

	UPROPERTY(EditAnywhere, Category="DamageType")
	TSubclassOf<UDamageType> DmgTypeClass;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<USoundBase> ExplosionSound;

	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> OnFireEffect;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	TObjectPtr<USoundBase> OnFireSoundLoop2;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> ActiveBurningEffectComp = nullptr;

	UPROPERTY()
	TObjectPtr<UAudioComponent> ActiveBurningSoundComp = nullptr;
	// Called when the game starts or when spawned

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Explode();

	bool bExploded = false;

	FTimerHandle ExplosionTimer;

public:
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, const struct FDamageEvent& DamageEvent,
	                         class AController* EventInstigator, AActor* DamageCauser) override;
};
