// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/DamageType.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Misc/MapErrors.h"


// Sets default values
ARogueExplosiveBarrel::ARogueExplosiveBarrel() 
	: ExplosionDelayTime(3.f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SocketName = FName("FireSocket");
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;
	
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionProfileName("PhysicsActor");
	
	RadForce = CreateDefaultSubobject<URadialForceComponent>("RadForce");
	RadForce->SetupAttachment(StaticMeshComp);
	
	RadForce->ImpulseStrength = 100000.0f;
	RadForce->Radius = 650.0f;
	RadForce->bAutoActivate = false;
	RadForce->bIgnoreOwningActor = true;
	
}

// Called when the game starts or when spawned
void ARogueExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
}

float ARogueExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	if (bExploded || GetWorldTimerManager().TimerExists(ExplosionTimer))
	{
		return ActualDamage;
	}
	
	ActiveBurningEffectComp = UNiagaraFunctionLibrary::SpawnSystemAttached(OnFireEffect, StaticMeshComp, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	ActiveBurningSoundComp = UGameplayStatics::SpawnSoundAttached(OnFireSoundLoop2, StaticMeshComp);
	
	GetWorldTimerManager().SetTimer(ExplosionTimer, this, &ARogueExplosiveBarrel::Explode, ExplosionDelayTime);
	
	return ActualDamage;
}

void ARogueExplosiveBarrel::Explode()
{
	bExploded = true;	
	ActiveBurningEffectComp->Deactivate();
	ActiveBurningSoundComp->Stop();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
	
	RadForce->FireImpulse();
	
	Destroy();
}

