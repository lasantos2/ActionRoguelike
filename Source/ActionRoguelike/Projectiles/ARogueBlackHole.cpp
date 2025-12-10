// Fill out your copyright notice in the Description page of Project Settings.

#include "ARogueBlackHole.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

AARogueBlackHole::AARogueBlackHole()
{
	RadForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadForce"));
	RadForce->SetupAttachment(RootComponent);
	RadForce->ForceStrength = DefaultRadForce;
	RadForce->Radius = 4000.0f;
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	RadForce->bIgnoreOwningActor = true;
	RadForce->AddCollisionChannelToAffect(ECC_PhysicsBody);
	RadForce->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	SphereComp->SetSphereRadius(60.f);
	
	FCollisionResponseContainer Colls; 
	
	Colls.SetAllChannels(ECR_Ignore);
	Colls.SetResponse(ECC_WorldDynamic, ECR_Overlap);
	Colls.SetResponse(ECC_WorldStatic, ECR_Overlap);
	Colls.SetResponse(ECC_PhysicsBody, ECR_Overlap);
	Colls.SetResponse(ECC_Vehicle, ECR_Overlap);
	Colls.SetResponse(ECC_Destructible, ECR_Overlap);
	
	SphereComp->SetCollisionResponseToChannels(Colls);
}

void AARogueBlackHole::BeginPlay()
{
	Super::BeginPlay();

	RadForce->SetAutoActivate(true);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARogueBlackHole::OnComponentBeginOverlap);
	GetWorldTimerManager().SetTimer(BlackHoleDelayHandle, this, &AARogueBlackHole::BlackHoleTimerEnd, BlackHoleDelay);
}

void AARogueBlackHole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComp->OnComponentHit.RemoveAll(this);
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARogueBlackHole::OnComponentBeginOverlap);
}


void AARogueBlackHole::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                               const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}
