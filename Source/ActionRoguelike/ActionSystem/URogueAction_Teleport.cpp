// Fill out your copyright notice in the Description page of Project Settings.


#include "URogueAction_Teleport.h"

#include "NiagaraFunctionLibrary.h"
#include "RogueActionSystemComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


void UURogueAction_Teleport::StartAction_Implementation()
{
	
	URogueActionSystemComponent* ActionComponent = GetOwningComponent();
	
	ACharacter* OwningChar = CastChecked<ACharacter>(ActionComponent->GetOwner());
	
	OwningChar->PlayAnimMontage(AttackMontage);	

	FTimerHandle AttackTimerHandle;
	constexpr float AttackDelayTime = 0.2f;
	//GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &ARoguePlayerCharacter::AttackTimerElapsed, AttackDelayTime);

	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, OwningChar->GetMesh(), MuzzleSocketName, FVector::ZeroVector,
												 FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);

	UGameplayStatics::PlaySound2D(this, CastingSound);

}
