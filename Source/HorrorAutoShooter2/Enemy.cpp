// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/CapsuleComponent.h"
#include "Bonus.h"
#include "Engine/TimerHandle.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "HorrorGameMode.h"


AEnemy::AEnemy()
{   
    AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollision"));
    if (AttackCollision != nullptr)
    {
        AttackCollision->InitSphereRadius(15.f);
        AttackCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("MeleeSocket"));
    }

    HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
    HealthBar->SetupAttachment(RootComponent);

    SetMovementSpeed(125.f);
    
}

void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    if(PlayerPawn)
    {
        if(InAttackRange())
        {
            Attack();
        }
    }
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    if (AttackCollision != nullptr)
    {   
        // Here we set the function, which will be called when the enemy colides with the character
        AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
    }    
    // Set the default Enemy walkspeed
    GetCharacterMovement()->MaxWalkSpeed = MovementSpeed;
}

void AEnemy::BonusDrop()
{
    // Spawn Bonus when Enemy dies
    TSubclassOf<ABonus> BonusObject = ABonus::StaticClass(); 
    GetWorld()->SpawnActor<ABonus>(BonusObject, GetActorLocation(), GetActorRotation());
}

void AEnemy::Attack()
{
    // Timer delegate needs to call the timer function with input parameters
    FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemy::SetbHit, true);
    GetWorld()->GetTimerManager().SetTimer(AttackTimer, TimerDelegate, AttackDelay, true);
}

// Overlap function (called, when enemy collides with other actor)
void AEnemy::OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        // UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
	    // UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName());
        AController* EnemyController = GetController();
        ABaseCharacter* PlayerChar = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

        UClass* DamageTypeClass = UDamageType::StaticClass();
        
        if (PlayerChar != nullptr)
        {
            AttackDamage = FMath::Min(PlayerChar->GetHealth(), AttackDamage);
        }

        // Here we prevent the self-damage, frendly-damage, check the hit event and damage delay
        if (OtherActor && OtherActor != this && !OtherActor->IsA(AEnemy::StaticClass()) && bHit && bDamageDeal)
        {
            // UE_LOG(LogTemp, Error, TEXT("YOU CAN DEAL DAMAGE!"));
            // Here is the timer that delays the damage applying to the player
            FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemy::SetDealDamageDelay, true);
            GetWorld()->GetTimerManager().SetTimer(DamageTimer, TimerDelegate, DamageDelay, true);

            UGameplayStatics::ApplyDamage(OtherActor, AttackDamage, EnemyController, this, DamageTypeClass);
            SetDealDamageDelay(false);
        }  
    }
}

/*void AEnemy::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {

    }
}*/

/*void AEnemy::DamageOnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    UE_LOG(LogTemp, Warning, TEXT("OverlappedActor: %s"), *OverlappedActor->GetName());
    AController* EnemyController = GetController(); //Cast<AController>(this->GetController());
    UClass* DamageTypeClass = UDamageType::StaticClass();
    AttackDamage = FMath::Min(this->GetHealth(), AttackDamage);

    UGameplayStatics::ApplyDamage(OtherActor, AttackDamage, EnemyController, this, DamageTypeClass);
}*/

// Hit function (called, when enemy collides with other actor)
/*void AEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{
    //SetbHit(true);
	UE_LOG(LogTemp, Warning, TEXT("OnActorHit!"));
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName());

    AController* EnemyController = GetController(); //Cast<AController>(this->GetController());
	//AController* MyOwnInstigator = Cast<AController>(UGameplayStatics::GetPlayerController(this, 0));
	UClass* DamageTypeClass = UDamageType::StaticClass();

    // Set the damage value to avoid negative value of health
    AttackDamage = FMath::Min(this->GetHealth(), AttackDamage);

	if (OtherActor && OtherActor != this && !OtherActor->IsA(AEnemy::StaticClass()) && bHit)
	{   
        // Here we Apply the Damage to the OtherActor
		UGameplayStatics::ApplyDamage(OtherActor, AttackDamage, EnemyController, this, DamageTypeClass);
		// Add the Particles, Sound and Camera Shake effects
        SetbHit(false);
        
	}
    // SetbHit(false);
}*/

bool AEnemy::IsHit()
{
    return bHit;
}

void AEnemy::SetbHit(bool NewHit)
{
    bHit = NewHit;
}

void AEnemy::SetDealDamageDelay(bool bWaitAttack)
{
    bDamageDeal = bWaitAttack;
}

bool AEnemy::InAttackRange()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    FVector EnemyLocation = this->GetActorLocation(); 
    FVector PlayerLocation = PlayerPawn->GetActorLocation();

    // Get the distance between the enemy and the player
    float DistanceToPlayer = FVector::Distance(PlayerLocation, EnemyLocation);

    return DistanceToPlayer <= AttackRange;
}

void AEnemy::Die()
{
    DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    
    // We hide the enemy's health bar before it disappears
    HealthBar->SetHiddenInGame(true);
    AHorrorGameMode* GameMode = GetWorld()->GetAuthGameMode<AHorrorGameMode>();
	if (GameMode != nullptr)
		{
			GameMode->SetEnemyKilledScore();
		}
    // Here we have an experience drop
    // BonusDrop();
}

float AEnemy::GetAttackRange() const
{
    return AttackRange;
}