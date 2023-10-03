// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"


AEnemy::AEnemy()
{   
    // Set the default Enemy walkspeed
    GetCharacterMovement()->MaxWalkSpeed = 200.f;
}
