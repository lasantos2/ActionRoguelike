// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RougueCharacter.generated.h"

class ARogueProjectileMagic;
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
struct FInputActionInstance;

UCLASS(Abstract)
class ACTIONROGUELIKE_API ARougueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARougueCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere, Category="Primary Attack")
	FName MuzzleSocketName;
	
	UPROPERTY(EditDefaultsOnly, Category="Primary Attack")
	TSubclassOf<ARogueProjectileMagic> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> CameraComp;
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	void PrimaryAttack();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
