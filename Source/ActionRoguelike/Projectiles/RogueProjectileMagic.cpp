
#include "RogueProjectileMagic.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARogueProjectileMagic::ARogueProjectileMagic()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetSphereRadius(16.0f);
	SphereComp->SetCollisionProfileName("Projectile");
	
	RootComponent = SphereComp;
	
	LoopedNiagaraComp = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComp->SetupAttachment(SphereComp);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	
}

void ARogueProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &ARogueProjectileMagic::OnActorHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ARogueProjectileMagic::OnActorHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// @todo: create our own damage type
	TSubclassOf<UDamageType> DmgTypeClass = UDamageType::StaticClass();
	UGameplayStatics::ApplyDamage(OtherActor, 10.f, GetInstigatorController(), this, DmgTypeClass);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
	
	Destroy();
}