// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

struct FGameplayTag;
class URogueAction;
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
	
	void StartAction(FGameplayTag InActionName);
	
	void StopAction(FGameplayTag InActionName);
	
	UFUNCTION(BlueprintCallable)
	void ApplyHealthChange(float InValueChange);
	
	UFUNCTION(BlueprintCallable)
	float GetAttributeHealth() const {return Attributes.Health;};
	
	UFUNCTION(BlueprintCallable)
	float GetAttributeHealthMax();
	
	UFUNCTION(BlueprintCallable)
	bool IsFullHeath();
	
	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;
	
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attributes")
	FRogueAttributeSet Attributes;
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
public:
	URogueActionSystemComponent();
	
	virtual void InitializeComponent() override;
};
