// Fill out your copyright notice in the Description page of Project Settings.


#include "HorrorAIController.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Math/Vector.h"


void AHorrorAIController::BeginPlay()
{
    Super::BeginPlay();

}

void AHorrorAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    AEnemy* EnemyPawn = Cast<AEnemy>(GetPawn());
        
    if (LineOfSightTo(PlayerPawn))
    {   
        // Set Focus and go to the Player
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn, AcceptanceRadius);
        

        if (PlayerPawn && InAttackRange())
        {
            EnemyPawn->SetbHit(true);
            AController* MyOwnInstigator = Cast<AController>(this);
            UClass* DamageTypeClass = UDamageType::StaticClass();

            /*if (PlayerPawn && PlayerPawn != EnemyPawn)
            {
                // Here we Apply the Damage to the OtherActor
                //UGameplayStatics::ApplyDamage(PlayerPawn, AEnemy::Attack(), MyOwnInstigator, Cast<AActor>(GetPawn()), DamageTypeClass);
                EnemyPawn->Attack();
                //UGameplayStatics::ApplyDamage(Cast<AActor>(PlayerPawn), EnemyPawn->Attack());
                // Add the Particles, Sound and Camera Shake effects
            }*/
        }
    }
    else
    {   
        // if Enemy doesn't see the Player
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}

bool AHorrorAIController::InAttackRange()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    AEnemy* EnemyPawn = Cast<AEnemy>(GetPawn());
    FVector EnemyLocation = EnemyPawn->GetActorLocation(); 
    FVector PlayerLocation = PlayerPawn->GetActorLocation();
    float DistanceToPlayer = FVector::Distance(PlayerLocation, EnemyLocation);

    return DistanceToPlayer <= (AcceptanceRadius + 100);
}