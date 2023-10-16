// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/CapsuleComponent.h"
#include "Bonus.h"
#include "Engine/TimerHandle.h"
#include "Components/SphereComponent.h"


AEnemy::AEnemy()
{   
    AttackCollision = CreateDefaultSubobject<USphereComponent>(TEXT("AttackCollision"));
    if (AttackCollision != nullptr)
    {
        AttackCollision->InitSphereRadius(15.f);
        AttackCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("MeleeSocket"));
    }

    // Set the default Enemy walkspeed
    GetCharacterMovement()->MaxWalkSpeed = 200.f;
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

/*AEnemy::~AEnemy()
{
    AEnemy* EnemyPawn = Cast<AEnemy>(GetOwner());
    // Drag it to the Die() function, because in the destructor it will be too late
    TSubclassOf<ABonus> BonusObject = ABonus::StaticClass();
    GetWorld()->SpawnActor<ABonus>(BonusObject, EnemyPawn->GetActorLocation(), EnemyPawn->GetActorRotation());
}*/

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    //AttackCollision = GetWorld()->SpawnActor<USphereComponent>(SphereClass);
   

    // Here we set the function, which will be called when the enemy colides with the character
    // GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);
    if (AttackCollision != nullptr)
    {
        AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
    }
    // Timer delegate needs to call the timer function with input parameters
    
}

void AEnemy::Attack()
{
    FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AEnemy::SetbHit, true);
    GetWorld()->GetTimerManager().SetTimer(AttackTimer, TimerDelegate, AttackDelay, true);

    // return FMath::Min(this->GetHealth(), AttackDamage);
}

void AEnemy::OnOverlapBegin(class UPrimitiveComponent* Comp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
	    UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName());
        AController* EnemyController = GetController();
        UClass* DamageTypeClass = UDamageType::StaticClass();
        AttackDamage = FMath::Min(this->GetHealth(), AttackDamage);
        // Here we prevent the self-damage, frendly-damage, check the hit event and damage delay
        if (OtherActor && OtherActor != this && !OtherActor->IsA(AEnemy::StaticClass()) && bHit && bDamageDeal)
        {
            UE_LOG(LogTemp, Error, TEXT("YOU CAN DEAL DAMAGE!"));
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
    //AEnemy* EnemyPawn = Cast<AEnemy>(GetPawn());
    FVector EnemyLocation = this->GetActorLocation(); 
    FVector PlayerLocation = PlayerPawn->GetActorLocation();
    // Get the distance between the enemy and the player
    float DistanceToPlayer = FVector::Distance(PlayerLocation, EnemyLocation);

    return DistanceToPlayer <= 150.f;
}