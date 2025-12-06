// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueProjectileMagic.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraComponent;
class UAudioComponent;
class UNiagaraSystem;
class USoundBase;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueProjectileMagic : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UDamageType> DmgTypeClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USphereComponent> SphereComp;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComp;	
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	
	virtual void PostInitializeComponents() override;
	

	ARogueProjectileMagic();


};
