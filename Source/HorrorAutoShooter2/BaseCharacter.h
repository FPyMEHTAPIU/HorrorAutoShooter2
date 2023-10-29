// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class HORRORAUTOSHOOTER2_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	virtual void Die();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealth() const;
	//void SetHealth(float GetDamage);
	UFUNCTION(BlueprintPure)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(float HealValue);

	UPROPERTY(EditAnywhere)
	float RotationRate = 50.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 20.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float Health = 10.f;

	
	
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	//UFUNCTION()
	//void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* MyOwnInstigator, AActor* DamageCauser);

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//class UHealthComponent* HealthComponent;

	FVector2D PreviousMousePosition;
	FVector2D CurrentMousePosition;

	float CalculateMouseSpeed();

	UInputComponent* MyInputComponent;

	UPROPERTY(EditAnywhere)
	float SpeedMultiplier = 5.f;
};
