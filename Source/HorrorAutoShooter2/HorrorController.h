// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HorrorController.generated.h"

/**
 * 
 */
class UUserWidget;

UCLASS()
class HORRORAUTOSHOOTER2_API AHorrorController : public APlayerController
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	FTimerHandle RestartTimer;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDClass;

	UUserWidget* HUD;	
};
