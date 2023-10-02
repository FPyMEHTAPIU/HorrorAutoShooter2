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

	/*UFUNCTION(BlueprintPure)
	bool IsDead() const;*/

	/*virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, AActor* DamageCauser);*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*UPROPERTY(EditAnywhere)
	float Health = 0.f;
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 30.f;*/
	
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 1.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
  	class USpringArmComponent* SpringArm;
  	UPROPERTY(VisibleAnywhere, Category = "Components")
  	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	float RotationRate = 50.f;

	void Die();

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
};
