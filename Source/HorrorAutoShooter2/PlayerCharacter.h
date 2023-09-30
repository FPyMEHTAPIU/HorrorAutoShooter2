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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	float Experience = 0.f;
	UPROPERTY(VisibleAnywhere)
	float Level = 0.f;

	template <class T>
	T GrabBonus(T Bonus);

	void ChooseBonus();
	void LevelUp();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;
};
