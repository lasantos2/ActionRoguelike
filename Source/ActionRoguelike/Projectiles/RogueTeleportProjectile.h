// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueTeleportProjectile.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueTeleportProjectile : public ARogueProjectile
{
	GENERATED_BODY()

public:
	ARogueTeleportProjectile();

protected:
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& Hit) override;
	
	UPROPERTY(EditAnywhere, Category="ProjectileSettings")
	float TeleportAppearDelay{3.0f};
	
	UPROPERTY(EditAnywhere, Category="ProjectileSettings")
	float TeleportMoveDelay{3.0f};
	
	UPROPERTY(VisibleAnywhere, Category="ProjectileSettings")
	bool bPortalAppeared{false};
	
	//Actual portal effect + sound
	UPROPERTY(EditDefaultsOnly, Category="ProjectileSettings")
	TObjectPtr<UNiagaraSystem> TeleportPortalEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="ProjectileSettings")
	TObjectPtr<USoundBase> TeleportPortalSound;
	
	// Effect + sound before portal appears + disappears
	UPROPERTY(EditDefaultsOnly, Category="ProjectileSettings")
	TObjectPtr<UNiagaraSystem> TeleportExplodeEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="ProjectileSettings")
	TObjectPtr<USoundBase> TeleportExplodeSound;
	
	// When goes off should explode and create teleport portal
	FTimerHandle TeleportDelayActivateTimer;
	FTimerHandle MoveDelayTimer;


	
public:
	
	UFUNCTION()
	void TeleportAppear();
	
	UFUNCTION()
	void TeleportMove();
	
	virtual void BeginPlay() override;
	
};
