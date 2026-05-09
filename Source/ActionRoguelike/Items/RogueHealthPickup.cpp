// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/RogueHealthPickup.h"

#include "SharedGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "ActionSystem/RogueActionSystemComponent.h"
#include "Core/RogueGameplayStatics.h"

float ARogueHealthPickup::GetHealthAmount()
{
	return HealthAmount;
}

void ARogueHealthPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueHealthPickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	TObjectPtr<URogueActionSystemComponent> actionSystem = Cast<URogueActionSystemComponent>(OtherActor->GetComponentByClass(URogueActionSystemComponent::StaticClass()));
	
	// From Tom
	if (ensure(actionSystem != nullptr) && !URogueGameplayStatics::IsFullHealth(actionSystem))
	{
		actionSystem->ApplyAttributeChange(SharedGameplayTags::Attribute_Health,HealthAmount, Base);
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation(), FRotator::ZeroRotator);
		Destroy();
	}
	
}
