// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "ARogueBlackHole.generated.h"

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AARogueBlackHole : public ARogueProjectile
{
	GENERATED_BODY()

public:
	AARogueBlackHole();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<URadialForceComponent> RadForce;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	float DefaultRadForce{-4000000.f};

	FTimerHandle BlackHoleDelayHandle;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	float BlackHoleDelay{5.0f};

	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                     const FHitResult& SweepResult);


	void BlackHoleTimerEnd();
};

inline void AARogueBlackHole::BlackHoleTimerEnd()
{
	// Play the portal blink off animation


	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Magenta, FString("Getting tired time out"));
	Destroy();
}
