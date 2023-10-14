// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HorrorAIController.generated.h"

/**
 * 
 */
UCLASS()
class HORRORAUTOSHOOTER2_API AHorrorAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaSeconds) override;
	//bool IsDead() const;
	UFUNCTION(BlueprintPure)
	bool InAttackRange();

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior;

	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 0.f;

	//class AEnemy* EnemyPawn;
};
