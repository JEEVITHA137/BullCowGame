// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BullCowGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BULLCOWGAME_API ABullCowGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void HealthValue();

	void ScoreValue();

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	float Getscore() const;

	UFUNCTION(BlueprintPure)
	bool IsEnd() const;

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 15;

	UPROPERTY(VisibleAnywhere)
	float Health;

	float  Playerscore;
};
