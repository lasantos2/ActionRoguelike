// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RogueInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"


UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor, public IRogueInteractionInterface
{
	GENERATED_BODY()

public:
	ARogueItemChest();
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	float CurrentAnimationPitch = 0.f;
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	float AnimationTargetPitch = 120.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Animation")
	float AnimationSpeed = 50.f;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ChestAnimationComplete();

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact_Implementation() override;
};
