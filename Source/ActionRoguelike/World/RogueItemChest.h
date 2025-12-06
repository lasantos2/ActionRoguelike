// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RogueItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueItemChest : public AActor
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

protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
