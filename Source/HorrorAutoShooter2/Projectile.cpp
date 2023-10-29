// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "HealthComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->InitialSpeed = 2000.f;
}

void AProjectile::SetDamage(float NewDamage)
{
	Damage = NewDamage;
}

float AProjectile::GetDamage() const
{
	return Damage;
}

void AProjectile::IncreaseDamage(float IncreaseDamage)
{
	Damage += IncreaseDamage;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnHit!"));
	AActor* MyOwner = GetOwner();

	if (MyOwner != nullptr)
	{
		Destroy();
		// UE_LOG(LogTemp, Warning, TEXT("MyOwner: %s"), *MyOwner->GetName());
		return;
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.Location, GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.Location, 0.25f);
	// UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName()); uncom this
	// UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName()); uncom this
	//UE_LOG(LogTemp, Warning, TEXT("MyOwner: %s"), *MyOwner->GetName());

	AController* MyOwnInstigator = Cast<AController>(UGameplayStatics::GetPlayerController(this, 0));
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// Here we Apply the Damage to the OtherActor
		// UE_LOG(LogTemp, Error, TEXT("Damage Deal: %f"), Damage);
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnInstigator, this, DamageTypeClass);

		// Add the Particles, Sound and Camera Shake effects
	}
	Destroy();
}

