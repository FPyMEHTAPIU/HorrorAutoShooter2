// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AHorrorController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, HUDClass);
    if (HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}
