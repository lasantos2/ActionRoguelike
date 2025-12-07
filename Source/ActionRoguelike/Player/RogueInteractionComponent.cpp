// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "CollisionShape.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"
#include "RogueGameTypes.h"

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void URogueInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController *PC = CastChecked<APlayerController>(this->GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();
	
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	
	FCollisionShape Shape;
	
	Shape.SetSphere(InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	
	float HighestDotResult = -1.0;
	AActor* BestActor = nullptr;	
	
	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		
		FVector OverlapDirection = (OverlapLocation - Center).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());
	
		if (DotResult > HighestDotResult)
		{
			BestActor = Overlap.GetActor();
			HighestDotResult = DotResult;
		}
		FString DebugString = FString::Printf(TEXT("DOT: %f"), DotResult);
		
		DrawDebugString(GetWorld(), OverlapLocation,  DebugString, nullptr, FColor::White, 0.0f, true);
		
		DrawDebugBox(GetWorld(), OverlapLocation, FVector(50.0f), FColor::Red);
	}

	if (BestActor != nullptr)
	{
		SelectedActor = BestActor;
		DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.f), FColor::Green);
	}
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
}

void URogueInteractionComponent::Interact()
{

	if (SelectedActor != nullptr)
		IRogueInteractionInterface::Execute_Interact(SelectedActor);
}
