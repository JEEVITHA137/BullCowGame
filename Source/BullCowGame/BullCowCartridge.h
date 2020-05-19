// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct BullCowCount{
   int32 Bulls=0;
   int32 Cows=0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void SetUpGame();
    void EndGame();
	void ProcessGuess(const FString& Guess);
	bool IsIsogram(const FString& Word)const;
	TArray<FString> GetValidWords(const TArray<FString>&)const;
	BullCowCount GetBullCow(const FString& Guess)const;
	void GameInstruction();
	void SetGameVariables();
	void GuessNext();

	// Your declarations go below!
	private:
    FString Hiddenword;
    int32 Lives;
	bool bGameOver;
	TArray<FString> Isogram;
	int32 PlayerScore;
};