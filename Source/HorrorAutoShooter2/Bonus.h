// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonus.generated.h"

UCLASS()
class HORRORAUTOSHOOTER2_API ABonus : public AActor
{
	GENERATED_BODY()
	
public:	
	float GetValue() const;

protected:
	// Sets default values for this actor's properties
	ABonus();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetValue(float NewValue);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float Value = 0.f;
	UPROPERTY(EditAnywhere)
	float LifeTime = 20.f;

	// Add StaticMesh
};


