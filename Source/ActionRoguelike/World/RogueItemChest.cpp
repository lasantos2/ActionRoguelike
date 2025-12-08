#include "RogueItemChest.h"
#include "Math/UnrealMathVectorCommon.h.inl"


ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	BaseMeshComponent->SetCollisionProfileName("Interaction");
	RootComponent = BaseMeshComponent;

	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComponent"));
	LidMeshComponent->SetCollisionProfileName("NoCollision");
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}


void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentAnimationPitch = FMath::FInterpConstantTo(CurrentAnimationPitch, AnimationTargetPitch, DeltaTime,
	                                                 AnimationSpeed);
	float ClampedValue = FMath::Clamp(CurrentAnimationPitch, 0.0f, AnimationTargetPitch);
	LidMeshComponent->SetRelativeRotation(FRotator(ClampedValue, 0.0f, 0.0f));

	if (FMath::IsNearlyEqual(ClampedValue, AnimationTargetPitch) && IsActorTickEnabled())
	{
		SetActorTickEnabled(false);
		ChestAnimationComplete();
	}
}

void ARogueItemChest::Interact_Implementation()
{
	//PlayAnimation
	SetActorTickEnabled(true);
}
