// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/RoguePickupActor.h"

#include "RogueGameTypes.h"
#include "Components/SphereComponent.h"

// Sets default values
ARoguePickupActor::ARoguePickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	RootComponent = BaseMeshComponent;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetCollisionProfileName(TEXT("Pickups"));
	CollisionComponent->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ARoguePickupActor::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARoguePickupActor::OnComponentBeginOverlap);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	
}

// Called every frame
void ARoguePickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoguePickupActor::Interact_Implementation()
{
	IRogueInteractionInterface::Interact_Implementation();
}

void ARoguePickupActor::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Purple, FString::Printf(TEXT("Picked up Item")));
	Destroy();
}


