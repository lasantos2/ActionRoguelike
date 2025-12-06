// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePlayerController.h"

#include "RogueInteractionComponent.h"

ARoguePlayerController::ARoguePlayerController()
{
	InteractComp = CreateDefaultSubobject<URogueInteractionComponent>(TEXT("InteractionComp"));
}
