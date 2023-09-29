// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

void APlayerCharacter::ChooseBonus()
{
    int32 BonusNumber = 0;
    // Need to get a bonuses from every? Bonus class and choose randomly 3 of them.
    /*switch(BonusNumber)
    {
        case 1:
        {
            
        }
        case 2:
        {
            
        }
        case 3:
        {
            
        }
    }*/
}


void APlayerCharacter::LevelUp()
{
    Level++;
    Experience -= 1000;
}


template<class T>
T APlayerCharacter::GrabBonus(T Bonus)
{
    
}
