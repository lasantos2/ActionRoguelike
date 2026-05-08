// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RogueAction.generated.h"

class URogueActionSystemComponent;
/**
 * 
 */
UCLASS(Blueprintable, Abstract)
class ACTIONROGUELIKE_API URogueAction : public UObject
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	FName ActionName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	float CooldownTime = 0.0f;
	
public:
	
	bool CanStart() const;
	
	bool IsRunning() const
	{
		return bIsRunning;
	}
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StartAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	void StopAction();
	
	float GetCooldownTimeRemaining() const
	{
		return FMath::Max(0.0f, CooldownUntil - GetWorld()->TimeSeconds);
	}
	FName GetActionName() const
	{
		return ActionName;
	}
	
	UFUNCTION(BlueprintCallable, Category = "Actions")
	URogueActionSystemComponent* GetOwningComponent() const;
	
protected:
	
	// Game time untile actions is available again
	UPROPERTY(Transient)
	float CooldownUntil = 0;
	
	UPROPERTY(Transient)
	bool bIsRunning = false;
};
