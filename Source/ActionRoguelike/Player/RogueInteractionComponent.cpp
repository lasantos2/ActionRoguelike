// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueInteractionComponent.h"

#include "CollisionShape.h"
#include "Core/RogueInteractionInterface.h"
#include "Engine/OverlapResult.h"
#include "RogueGameTypes.h"

TAutoConsoleVariable<bool> CVarInteractionDebugDrawing(TEXT("game.interaction.DebugDraw"), false, TEXT("Enable debug draw of Interaction. (0 = off, 1 = on)"), ECVF_Cheat );

URogueInteractionComponent::URogueInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void URogueInteractionComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APlayerController* PC = CastChecked<APlayerController>(this->GetOwner());

	FVector Center = PC->GetPawn()->GetActorLocation();
	FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();

	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;

	FCollisionShape Shape;

	Shape.SetSphere(InteractionRadius);

	TArray<FOverlapResult> Overlaps;
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	bool bEnabledDebugDraw = CVarInteractionDebugDrawing.GetValueOnGameThread();


	float HighestWeight = 0.0;
	AActor* BestActor = nullptr;

	for (FOverlapResult& Overlap : Overlaps)
	{
		FVector Origin;
		FVector BoxExtends;
		Overlap.GetActor()->GetActorBounds(true, Origin, BoxExtends);
	//	FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		FVector OverlapDirection = (Origin - CameraLocation).GetSafeNormal();

		
		float DistanceTo = (Origin - Center).SizeSquared();
		float DotResult = FVector::DotProduct(OverlapDirection, PC->GetControlRotation().Vector());

		float NormalizedDotResult = DotResult * .5f + .5f;
		float NormalizedDistanceTo = 1.0f - (DistanceTo / InteractionRadius);
		
		float Weight = (NormalizedDistanceTo*DistanceToWeightScale) + (NormalizedDotResult*DirectionWeightScale);
		if (Weight > HighestWeight)
		{
			BestActor = Overlap.GetActor();
			HighestWeight = Weight;
		}

		if (bEnabledDebugDraw)
		{
			FString DebugString = FString::Printf(TEXT("Weight: %f, Dot: %f, Dist: %f"), Weight, NormalizedDotResult, NormalizedDistanceTo);
			DrawDebugBox(GetWorld(), Origin, FVector(50.0f), FColor::Red);
			DrawDebugString(GetWorld(), Origin, DebugString, nullptr, FColor::White, 0.0f, true);
		}
	}

	SelectedActor = BestActor;
	
	if (bEnabledDebugDraw)
	{
		if (BestActor != nullptr)
		{
			DrawDebugBox(GetWorld(), BestActor->GetActorLocation(), FVector(60.f), FColor::Green);
		}
		DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
	}
}

void URogueInteractionComponent::Interact()
{
	if (SelectedActor != nullptr)
	{
		IRogueInteractionInterface::Execute_Interact(SelectedActor);
	}
}
