// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RougueCharacter.generated.h"

class ARogueProjectile;
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UAnimMontage;
class USoundBase;
class UNiagaraSystem;
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
	UPROPERTY(VisibleAnywhere, Category="PrimaryAttack")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<UNiagaraSystem> CastingEffect;

	UPROPERTY(EditDefaultsOnly, Category="SecondaryAttack")
	TObjectPtr<UNiagaraSystem> TeleportEffect;

	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TObjectPtr<USoundBase> CastingSound;

	UPROPERTY(EditDefaultsOnly, Category = "PrimaryAttack")
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(VisibleAnywhere, Category ="PrimaryAttack")
	TSubclassOf<ARogueProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="PrimaryAttack")
	TSubclassOf<ARogueProjectile> PrimaryProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="SecondaryAttack")
	TSubclassOf<ARogueProjectile> SecondaryProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="SpecialAttack")
	TSubclassOf<ARogueProjectile> SpecialProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_PrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> Input_SpecialAttack;


	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& InValue);
	void Look(const FInputActionInstance& InValue);
	void PrimaryAttack();
	void SecondaryAttack();
	void SpecialAttack();
	void AttackTimerElapsed();
	virtual void Jump() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
