// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "CollisionShape.h"
#include "Engine/OverlapResult.h"

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
	
	ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility;
	
	FCollisionShape Shape;
	
	Shape.SetSphere(InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	for (FOverlapResult& Overlap : Overlaps)
	{
		DrawDebugBox(GetWorld(), Overlap.GetActor()->GetActorLocation(), FVector(50.0f), FColor::Red);
		
	}
}
