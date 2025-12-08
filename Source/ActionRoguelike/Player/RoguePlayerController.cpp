// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePlayerController.h"

#include "RogueInteractionComponent.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"

ARoguePlayerController::ARoguePlayerController()
{
	InteractComp = CreateDefaultSubobject<URogueInteractionComponent>(TEXT("InteractionComp"));
}

void ARoguePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);

	EnhancedInput->BindAction(Input_Interact, ETriggerEvent::Triggered, this, &ARoguePlayerController::StartInteract);
}

void ARoguePlayerController::StartInteract()
{
	InteractComp->Interact();
}
