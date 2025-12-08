// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueTeleportProjectile.h"

#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

ARogueTeleportProjectile::ARogueTeleportProjectile()
{
}

void ARogueTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Purple, FString("Spawned Teleport Projectile"), true);

	// Timer to delay appearance of Portal
	GetWorldTimerManager().SetTimer(TeleportDelayActivateTimer, this, &ARogueTeleportProjectile::TeleportAppear,
	                                TeleportAppearDelay);
}

void ARogueTeleportProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// If hit detected, activate portal on area
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Purple, TEXT("TeleportHit"));

	GetWorldTimerManager().ClearTimer(TeleportDelayActivateTimer);
	TeleportDelayActivateTimer.Invalidate();
	TeleportAppear();
}

void ARogueTeleportProjectile::TeleportAppear()
{
	//bPortalAppeared = true;

	TeleportDelayActivateTimer.Invalidate();
	GetWorldTimerManager().ClearTimer(TeleportDelayActivateTimer);

	ProjectileMovement->StopMovementImmediately();

	LoopedNiagaraComp->SetAsset(TeleportPortalEffect);
	LoopedNiagaraComp->ActivateSystem();
	LoopedAudioComponent->SetSound(TeleportPortalSound);
	LoopedAudioComponent->Play();

	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Purple, FString("TeleportAppear"));

	GetWorldTimerManager().SetTimer(MoveDelayTimer, this, &ARogueTeleportProjectile::TeleportMove, TeleportMoveDelay);
}

void ARogueTeleportProjectile::TeleportMove()
{
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Purple, FString("TeleportMove"));
	AActor* Insti = GetInstigator();
	if (!Insti)
	{
		return;
	}

	Insti->TeleportTo(GetActorLocation(), FRotator::ZeroRotator);
	MoveDelayTimer.Invalidate();
	GetWorldTimerManager().ClearTimer(MoveDelayTimer);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TeleportExplodeEffect, GetActorLocation());

	UGameplayStatics::PlaySoundAtLocation(this, TeleportExplodeSound, GetActorLocation(), FRotator::ZeroRotator);
	Destroy(true);
}
