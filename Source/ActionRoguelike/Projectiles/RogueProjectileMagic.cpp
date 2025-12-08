
#include "RogueProjectileMagic.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"


void ARogueProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector HitFromDirection = GetActorRotation().Vector();
	
	// @todo: create our own damage type
	
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f,HitFromDirection, Hit, GetInstigatorController(), this, DmgTypeClass);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
	
	Destroy();
}

ARogueProjectileMagic::ARogueProjectileMagic()
{
}
