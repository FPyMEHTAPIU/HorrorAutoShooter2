// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorGameMode.h"
#include "GameFramework/Controller.h"
#include "EngineUtils.h"


void AHorrorGameMode::PawnKilled(APawn* PawnKilled)
{
    AController* PlayerController = Cast<AController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    EndGame(true);
}

void AHorrorGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
