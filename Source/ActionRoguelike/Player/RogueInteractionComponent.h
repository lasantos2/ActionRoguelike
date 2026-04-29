// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueInteractionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URogueInteractionComponent();

	void Interact();

protected:
	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;

	UPROPERTY(EditDefaultsOnly, Category = Interaction)
	float InteractionRadius = 800.f;
	
	
	UPROPERTY(EditDefaultsOnly, Category = Interaction)
	float DistanceToWeightScale = 2.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = Interaction)
	float DirectionWeightScale = 1.0f;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
