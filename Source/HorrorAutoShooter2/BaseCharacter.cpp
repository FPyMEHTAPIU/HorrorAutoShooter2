// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "HorrorGameMode.h"
#include "Components/CapsuleComponent.h"
//#include "HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

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

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
	//	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &ABaseCharacter::DamageTaken);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
}

void ABaseCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue * RotationRate * GetWorld()->GetDeltaSeconds() * MovementSpeed);
}

void ABaseCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue * RotationRate * GetWorld()->GetDeltaSeconds() * MovementSpeed);
}

float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
	class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	if (IsDead())
	{
		Die();
	}

	return DamageToApply;
}

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
