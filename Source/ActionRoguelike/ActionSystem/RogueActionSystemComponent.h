// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "RogueAttributeSet.h"
#include "Components/ActorComponent.h"
#include "RogueActionSystemComponent.generated.h"

class URogueAction;
// TODO: Blueprint support later but for now C++ Only
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayTag /*AttributeTag*/, float /*NewAttributeValue*/, float /*NewAttributeValue*/);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROGUELIKE_API URogueActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	void StartAction(FGameplayTag InActionName);
	
	void StopAction(FGameplayTag InActionName);

	UFUNCTION(BlueprintCallable)
	void ApplyAttributeChange(FGameplayTag AttributeTag, float Delta, EAttributeModifiedType ModifyType);
	
	FRogueAttribute* GetAttribute(FGameplayTag InAttributeTag);
	
	void GrantAction(TSubclassOf<URogueAction> NewActionClass);
	
	FGameplayTagContainer ActiveGameplayTags;
	
protected:
	
	UPROPERTY()
	TArray<TObjectPtr<URogueAction>> Actions;
	
	UPROPERTY()
	TObjectPtr<URogueAttributeSet> Attributes;
	
	UPROPERTY(EditAnywhere, Category=Attributes, NoClear)
	TSubclassOf<URogueAttributeSet> AttributeSetClass;
	
	TMap<FGameplayTag, FOnAttributeChanged> AttributeListeners;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Actions")
	TArray<TSubclassOf<URogueAction>> DefaultActions;
	
	TMap<FGameplayTag, FRogueAttribute*> CachedAttributes;
public:
	URogueActionSystemComponent();

	virtual void InitializeComponent() override;
	
	FOnAttributeChanged& GetAttributeListener(FGameplayTag AttributeTag);
	
	virtual void BeginPlay() override;
	
};
