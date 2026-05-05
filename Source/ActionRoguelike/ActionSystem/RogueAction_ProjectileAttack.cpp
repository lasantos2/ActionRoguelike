// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueAction_ProjectileAttack.h"

#include "NiagaraFunctionLibrary.h"
#include "Player/RoguePlayerCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "RogueGameTypes.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Projectiles/RogueProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


TAutoConsoleVariable<bool> CVarProjectileAdjustmentDebugDrawing(TEXT("game.projectile.DebugDraw"),  0.0f, TEXT("Enable projectile debug draw of Interaction. (0 = off, > 0 is duration)"), ECVF_Cheat );

URogueAction_ProjectileAttack::URogueAction_ProjectileAttack()
{
	MuzzleSocketName = "Muzzle_01";
}

void URogueAction_ProjectileAttack::StartAction()
{
	Super::StartAction();
	
	URogueActionSystemComponent* ActionComponent = GetOwningComponent();
	
	ACharacter* OwningChar = CastChecked<ACharacter>(ActionComponent->GetOwner());
	
	OwningChar->PlayAnimMontage(AttackMontage);	

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, OwningChar->GetMesh(), MuzzleSocketName, FVector::ZeroVector,
												 FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	FTimerHandle AttackTimerHandle;
	constexpr float AttackDelayTime = 0.2f;
	
	
	GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ThisClass::AttackTimerElapsed,AttackDelayTime, false);
}

void URogueAction_ProjectileAttack::AttackTimerElapsed()
{
	URogueActionSystemComponent* ActionComponent = GetOwningComponent();
	
	ACharacter* OwningChar = CastChecked<ACharacter>(ActionComponent->GetOwner());
	
	FVector SpawnLocation = OwningChar->GetMesh()->GetSocketLocation(MuzzleSocketName);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = OwningChar;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FHitResult Hit;
	FVector EyeLocation;
	FRotator EyeRotation;
	
	OwningChar->GetController()->GetPlayerViewPoint(EyeLocation, EyeRotation);
	
	
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwningChar);
	
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 5000.f);
	
	
	UWorld* World = GetWorld();
	FVector AdjustTargetLocation;
	if (World->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ROGUE_PROJECTILE,QueryParams))
	{
		AdjustTargetLocation = Hit.Location;
	} 
	else
	{
		AdjustTargetLocation = TraceEnd;
	} 
	
	FRotator SpawnRotation = (AdjustTargetLocation - SpawnLocation).Rotation();
	AActor* NewProjectile = World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation,
													   SpawnParameters);

	OwningChar->MoveIgnoreActorAdd(NewProjectile);
	
	
#if !UE_BUILD_SHIPPING	
	
	float DebugDrawDuration = CVarProjectileAdjustmentDebugDrawing.GetValueOnGameThread();
	if (DebugDrawDuration > 0.0f)
	{
		// the hit location or trace end
		DrawDebugLine(World, AdjustTargetLocation, FVector(20.0f), FColor::Green, false, DebugDrawDuration);
	
		// Adjustment line trace
		DrawDebugLine(World, EyeLocation, TraceEnd, FColor::Green, false, DebugDrawDuration);
	
		// New projectile path
		DrawDebugLine(World, SpawnLocation, AdjustTargetLocation, FColor::Yellow, false, DebugDrawDuration);
	
		// Original projectile path
		DrawDebugLine(World, SpawnLocation, SpawnLocation * (EyeRotation.Vector() * 5000.f), FColor::Purple, false, DebugDrawDuration);
		
	}
#endif

}

