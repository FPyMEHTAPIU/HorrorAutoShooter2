// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HorrorGameMode.generated.h"

/**
 * 
 */
UCLASS()
class HORRORAUTOSHOOTER2_API AHorrorGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled);

private:
	void EndGame(bool bIsPlayerWinner);
};
