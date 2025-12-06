

#include "RogueItemChest.h"

#include "NiagaraTypes.h"
#include "VectorTypes.h"
#include "Math/UnrealMathVectorCommon.h.inl"


ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComponent"));
	RootComponent = BaseMeshComponent;
	
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComponent"));
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ARogueItemChest::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorTickEnabled(true);
	
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentAnimationPitch = FMath::FInterpConstantTo(CurrentAnimationPitch, AnimationTargetPitch, DeltaTime, AnimationSpeed);
	float ClampedValue = FMath::Clamp(CurrentAnimationPitch, 0.0f, AnimationTargetPitch);
	LidMeshComponent->SetRelativeRotation(FRotator(ClampedValue, 0.0f, 0.0f));
	
	if (FMath::IsNearlyEqual(ClampedValue, AnimationTargetPitch))
	{
		SetActorTickEnabled(false);
	}
}

