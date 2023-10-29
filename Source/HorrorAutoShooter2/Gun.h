// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class HORRORAUTOSHOOTER2_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

	UFUNCTION(BlueprintCallable)
	void SetFireRate(float FireRateDecreasePercent);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FTimerHandle ShootTimer;
	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere)
	float FireRate = 1.f;

private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;
	// UPROPERTY(EditAnywhere)
	// UParticleSystem* EmitterEffect;
	UPROPERTY(EditAnywhere)
	USoundBase* ShootSound;

	// Create a class for Projectile
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> ProjectileClass;
};
