// Fill out your copyright notice in the Description page of Project Settings.


#include "BullCowGameGameModeBase.h"

void ABullCowGameGameModeBase::BeginPlay() 
{
    Super::BeginPlay();

	Health = MaxHealth;
    Playerscore = 0;
}

void ABullCowGameGameModeBase::HealthValue() 
{
    Health -= 1 ;
}

void ABullCowGameGameModeBase::ScoreValue() 
{
    Playerscore += 5;
}

float ABullCowGameGameModeBase::GetHealthPercent() const
{
    return Health / MaxHealth;
}

float ABullCowGameGameModeBase::Getscore() const
{
    return Playerscore;
}

bool ABullCowGameGameModeBase::IsEnd() const
{
    return Health<=0;
}

