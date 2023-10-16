// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Gun.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    //GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));    
	Camera->SetupAttachment(SpringArm);

    /*
    //Setting class variables of the spring arm
    //SpringArm->bUsePawnControlRotation = true;
    //Setting class variables of the Character movement component
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->bUseControllerDesiredRotation = true;
    GetCharacterMovement()->bIgnoreBaseRotation = true;*/

    // Set the default Player walkspeed
    GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    //GetCharacterMovement()->bOrientRotationToMovement = true;
    // Destroy the Gun object, when player has died
    if (this->GetHealth() <= 0.f)
    {
        Gun->Destroy();
    }
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Set the Player's MoveSpeed
    APlayerCharacter::MovementSpeed = 500.f;
    // Spawn a gun with the PlayerCharacter
    Gun = GetWorld()->SpawnActor<AGun>(GunClass);
    // Hide a default gun mesh in character's skeletal mesh
    GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
    // Attach the gun mesh to the character's socket
    if (Gun != nullptr)
    {
        Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
        Gun->SetOwner(this);
    }

    //GetOwner()->OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::TakeDamage);
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
    Experience -= 100;
}

// A function must works with the different types of Bonuses (e.g. Heal, Experience, FireRate, MovementSpeed of something another)
template<class T>
T APlayerCharacter::TGrabBonus(T Bonus)
{
    
}