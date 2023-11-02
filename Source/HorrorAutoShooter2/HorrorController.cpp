// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerCharacter.h"


void AHorrorController::BeginPlay()
{
    Super::BeginPlay();

    // HUD = CreateWidget(this, HUDClass);
    // if (HUD != nullptr)
    // {
    //     HUD->AddToViewport();
    // }
}

void AHorrorController::Tick(float DeltaTime)
{
    APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(GetPawn());
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, true, Hit);
    
    if(PlayerPawn != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Clicked: %f"), PlayerPawn->GetbLMBHit());
    }
    

    if (PlayerPawn != nullptr && PlayerPawn->GetbLMBHit())
    {
        FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(PlayerPawn->GetActorLocation(), Hit.Location);
        PlayerPawn->AddMovementInput(Direction);
    }
}
