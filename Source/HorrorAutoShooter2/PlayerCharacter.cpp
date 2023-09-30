// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Gun.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;
    // Set the Player's MoveSpeed
    APlayerCharacter::MovementSpeed = 500.f;
    // Spawn a gun with the PlayerCharacter
    if (Gun != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Actor's Name: %s"), *Gun->GetActorNameOrLabel());
    }
    Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    if (Gun != nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Actor's Name: %s"), *Gun->GetActorNameOrLabel());
    }
    // Hide a default gun mesh in character's skeletal mesh
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
    // Attach the gun mesh to the character's socket
    if (Gun != nullptr)
    {
        Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
        Gun->SetOwner(this);
    }
}

void APlayerCharacter::ChooseBonus()
{
    int32 BonusNumber = 0;
    // Need to get a bonuses from every? Bonus class and choose randomly 3 of them.
    /*switch(BonusNumber)
    {
        case 1:
        {
            
        }
        case 2:
        {
            
        }
        case 3:
        {
            
        }
    }*/
}


void APlayerCharacter::LevelUp()
{
    Level++;
    Experience -= 1000;
}

// A function must works with the different types of Bonuses (e.g. Heal, Experience, FireRate, MovementSpeed of something another)
template<class T>
T APlayerCharacter::GrabBonus(T Bonus)
{
    
}