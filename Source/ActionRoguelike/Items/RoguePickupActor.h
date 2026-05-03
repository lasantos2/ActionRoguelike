// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/RogueInteractionInterface.h"
#include "RoguePickupActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
UCLASS()
class ACTIONROGUELIKE_API ARoguePickupActor : public AActor, public IRogueInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoguePickupActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<USphereComponent> CollisionComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<USoundBase> PickupSound;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Need Function for Item Overlap, Need a way to interface with this.
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;
	
	UFUNCTION()
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
										 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
										 const FHitResult& SweepResult);


};
