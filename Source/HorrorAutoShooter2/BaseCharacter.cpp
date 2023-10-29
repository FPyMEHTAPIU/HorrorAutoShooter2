// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "HorrorGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Bonus.h"
#include "GameFramework/PlayerInput.h"
//#include "HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

bool ABaseCharacter::IsDead() const
{
	/*if (HealthComponent)
	{
		//UE_LOG(LogTemp, Error, TEXT("HEALTH: %f"), HealthComponent->GetHealth());
		return HealthComponent->GetHealth() <= 0;
	}*/
	return Health <= 0;
	//return false;
}

float ABaseCharacter::GetHealth() const
{
	return Health;
}

float ABaseCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

void ABaseCharacter::SetHealth(float HealValue)
{
	Health += HealValue;
}

// void ABaseCharacter::SetHealth(float GetDamage)
// {
// 	Healh -= Damage;
// }

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	//GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ABaseCharacter::TakeDamage);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// MyInputComponent = InputComponent;

	/*if (MyInputComponent)
	{
		PreviousMousePosition = CurrentMousePosition;
    	CurrentMousePosition = FVector2D(MyInputComponent->GetAxisValue("MoveRight"), MyInputComponent->GetAxisValue("MoveForward"));
	}*/
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);
}

void ABaseCharacter::Die()
{
	// bIsDead = true;
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	/*ABaseCharacter* BaseCharPawn = Cast<ABaseCharacter>(GetOwner());
	TSubclassOf<ABonus> BonusObject = ABonus::StaticClass();
    GetWorld()->SpawnActor<ABonus>(BonusObject, BaseCharPawn->GetActorLocation(), BaseCharPawn->GetActorRotation());*/
		
}

void ABaseCharacter::MoveForward(float AxisValue)
{
	//float MouseX = GetMouseSensitivityX();
	// Find out which way is forward
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);
	// Get forward vector
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(Direction, AxisValue);
	//AddMovementInput(GetActorForwardVector() * AxisValue * RotationRate * GetWorld()->GetDeltaSeconds() * MovementSpeed);
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	//float MouseY = GetMouseSensitivityY();
	// Find out which way is right
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);
	// Get right vector 
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// Add movement in that direction
    AddMovementInput(Direction, AxisValue);
	//AddMovementInput(GetActorRightVector() * AxisValue * RotationRate * GetWorld()->GetDeltaSeconds() * MovementSpeed);
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
	class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// UE_LOG(LogTemp, Error, TEXT("Damage in parameter: %f"), DamageAmount);
	// UE_LOG(LogTemp, Error, TEXT("Damage Before Correcttion: %f"), DamageToApply);
	DamageToApply = FMath::Min(Health, DamageToApply);
	// UE_LOG(LogTemp, Error, TEXT("Damage Get: %f"), DamageToApply);
	Health -= DamageToApply;
	// UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	if (IsDead())
	{
		Die();
		SetLifeSpan(5.f);
	}

	return DamageToApply;
}

/*float ABaseCharacter::CalculateMouseSpeed()
{
	FVector2D MouseDelta = CurrentMousePosition - PreviousMousePosition;
    return SpeedMultiplier * MouseDelta.Size();
}*/

/*void ABaseCharacter::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, 
AController* MyOwnInstigator, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;
	Damage = FMath::Min(Health, Damage);
	Health -= Damage;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	// logic if character is dead
	if (IsDead())
	{
		ABaseCharacter* DeadChar = Cast<ABaseCharacter>(DamagedActor);
		DeadChar->Die();
	}
}*/
