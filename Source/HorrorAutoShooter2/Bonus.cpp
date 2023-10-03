// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonus.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABonus::ABonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BonusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BonusMesh"));
	RootComponent = BonusMesh;
}

float ABonus::GetValue() const
{
	return Value;
}

// Called when the game starts or when spawned
void ABonus::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(LifeTime);
}

void ABonus::SetValue(float NewValue)
{
	Value += NewValue;
}

// Called every frame
void ABonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

