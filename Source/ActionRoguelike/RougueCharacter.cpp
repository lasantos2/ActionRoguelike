// Fill out your copyright notice in the Description page of Project Settings.


#include "RougueCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Projectiles/RogueProjectileMagic.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARougueCharacter::ARougueCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
	

	MuzzleSocketName = FName("Muzzle_01");
}

// Called when the game starts or when spawned
void ARougueCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARougueCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();
	
//	FVector MoveDirection = FVector(InputValue.X, InputValue.Y, 0.0f);
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	
	
	AddMovementInput(ControlRot.Vector(), InputValue.X);
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARougueCharacter::Look(const FInputActionInstance& InValue)
{
	
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ARougueCharacter::PrimaryAttack()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation();
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = this;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass,SpawnLocation, SpawnRotation, SpawnParameters);	
}

// Called every frame
void ARougueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARougueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARougueCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARougueCharacter::Look);
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, &ARougueCharacter::PrimaryAttack);
}

