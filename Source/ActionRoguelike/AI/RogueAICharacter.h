// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RogueAICharacter.generated.h"

class URogueMonsterData;
struct FGameplayTag;
class URogueActionSystemComponent;
class UAnimMontage;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARogueAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARogueAICharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<URogueActionSystemComponent> ActionSystemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Animation")
	TObjectPtr<UAnimMontage> DeathMontage;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	virtual void PostInitializeComponents() override;
	
	UFUNCTION()
	void OnGameplayTagUpdated(FGameplayTag UpdatedTag, int32 NewCount);
	
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	TObjectPtr<UAnimMontage> StunnedAnimation;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	URogueMonsterData* GetMonsterData() const
	{
		return MonsterData;
	}
	
	void SetMonsterData(URogueMonsterData* NewMonsterData)
	{
		check(MonsterData == nullptr)
		MonsterData = NewMonsterData;
	}
	
	URogueActionSystemComponent* GetActionSystemComponent() const
	{
		return ActionSystemComponent;
	}

protected:
	FTimerHandle OverlayTimerHandle;
	
	UPROPERTY(Transient)
	TObjectPtr<URogueMonsterData> MonsterData;
};
