// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

USTRUCT(BlueprintType)
struct FRogueAttributeSet
{
	GENERATED_BODY()
	FRogueAttributeSet()
		: HealthMax(100.0f)
	{
		Health = HealthMax;
	}
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Health;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float HealthMax;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, OldHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	void ApplyHealthChange(float InValueChange);
	
	UFUNCTION(BlueprintCallable)
	float GetAttributeHealth() {return Attributes.Health;};
	
	UFUNCTION(BlueprintCallable)
	float GetAttributeHealthMax() {return Attributes.HealthMax;};
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attributes")
	FRogueAttributeSet Attributes;
public:
	URogueActionSystemComponent();
};
