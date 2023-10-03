// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorAIController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"


void AHorrorAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AHorrorAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        
    if (LineOfSightTo(PlayerPawn))
    {   
        // Set Focus and go to the Player
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn, AcceptanceRadius);
    }
    else
    {   
        // if Enemy doesn't see the Player
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}