// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
class AGun;

UCLASS()
class HORRORAUTOSHOOTER2_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetExperience(float ExpValue);

	UFUNCTION(BlueprintPure)
	float GetExperience();

	UFUNCTION(BlueprintPure)
	int32 GetLvl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
  	class USpringArmComponent* SpringArm;
  	UPROPERTY(VisibleAnywhere, Category = "Components")
  	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	float Experience = 0.f;
	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;

	template <class T>
	T TGrabBonus(T Bonus);

	void ChooseBonus();
	void LevelUp();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	APlayerController* SoldierPlayerController;

	// meta for edit private member in blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* PlayerHUD;
};
