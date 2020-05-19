// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    //Welcoming the player
    Super::BeginPlay();
   
    Isogram = GetValidWords(Words);
    SetGameVariables();
    GameInstruction();
    SetUpGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if(bGameOver)
    {
        ClearScreen();
        GameInstruction();
        SetUpGame();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetGameVariables()
{
    bGameOver=false;
}

void UBullCowCartridge::GameInstruction()
{
    if(bGameOver)
    {
        PrintLine(TEXT("Welcome to BullCowGame!..."));
    }
    else
    {
        PrintLine(TEXT("Welcome to BullCowGame!..."));
        PrintLine(TEXT("Guess the Isogram(No repeated letters)."));
        PrintLine(TEXT("BullCount:Letters with Correct Position."));
        PrintLine(TEXT("CowCount:Letters with Incorrect Position"));
        PrintLine(TEXT("Note:BullCount and CowCount are Zero(No\nletter matching)."));
    }
}

void UBullCowCartridge::SetUpGame(){
    
    Lives=15;
    PlayerScore=0;

    Hiddenword = Isogram[FMath::RandRange(0,Isogram.Num()-1)];

    PrintLine(TEXT("Guessing Word Length:%i"),Hiddenword.Len());
    PrintLine(TEXT("First Letter:%c"),Hiddenword[0]);
    PrintLine(TEXT("Lives:%i"),Lives);
    if(!bGameOver)
    {
        PrintLine(TEXT("Press Tab to start the game"));
    }
   
    bGameOver=false;
}

void UBullCowCartridge::GuessNext()
{
    Hiddenword = Isogram[FMath::RandRange(0,Isogram.Num()-1)];
    Lives+=5;
    PlayerScore+=15;

    PrintLine(TEXT("Correct!...Well Done..."));
    PrintLine(TEXT("Your Score:%i"),PlayerScore);
    PrintLine(TEXT("Guess again....Word Length:%i"),Hiddenword.Len());
    PrintLine(TEXT("First Letter:%c"),Hiddenword[0]);
    PrintLine(TEXT("Lives:%i"),Lives);
}

void UBullCowCartridge::EndGame(){
    
    bGameOver=true;

    PrintLine("\nPress Enter to Play again!...");
}

void UBullCowCartridge::ProcessGuess(const FString& Guess){
    
    if(Guess=="")
    {
        PrintLine(TEXT("Must Enter the Inputs"));
        return;
    }
    else
    {
        if(Guess==Hiddenword)
        {
            GuessNext();
            return;
        }

        if(Guess.Len() != Hiddenword.Len())
        {
            PrintLine(TEXT("The guessing word is %i letters word."),Hiddenword.Len());         
        }    
        
        if(!IsIsogram(Guess))
        {
            PrintLine(TEXT("No repeating letter in this word...."));
            return;
        }
        if(Lives<=10)
        {
        
            if(Guess[Guess.Len()-1]!=Hiddenword[Hiddenword.Len()-1]) 
            {
                PrintLine(TEXT("Hint:The last letter is %c"),Hiddenword[Hiddenword.Len()-1]);
            }

            if(Guess[Guess.Len()-1]==Hiddenword[Hiddenword.Len()-1]) 
            {
                PrintLine(TEXT("Hint:The second letter is %c"),Hiddenword[1]);
            }
        }
    }

    BullCowCount Score = GetBullCow(Guess);

    PrintLine(TEXT("You Lost the lives"));
    PrintLine(TEXT("Guess Again!..."));
    PrintLine(TEXT("Lives:%i"),--Lives);
    PrintLine(TEXT("You have %i Bulls and %i Cows"),Score.Bulls,Score.Cows);

    if(Lives<=0)
    {
        ClearScreen();
        PrintLine(TEXT("HiddenWord is %s"),*Hiddenword);
        PrintLine(TEXT("You have no more lives left"));
        EndGame();         
    }
}

bool UBullCowCartridge::IsIsogram(const FString& Word)const
{
    for(int32 Index=0;Index<Word.Len();Index++)
    {
        for(int32 Comaparison=Index+1;Comaparison<Word.Len();Comaparison++)
        {
            if(Word[Index]==Word[Comaparison])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList)const
{
    TArray<FString> ValidWord;
    for(FString Word:WordList)
    {
        if(Word.Len()>=4 && Word.Len()<=8 && IsIsogram(Word))
        {
              ValidWord.Emplace(Word);
        }
    }
    return ValidWord;
}

BullCowCount UBullCowCartridge::GetBullCow(const FString& Guess)const
{
    BullCowCount Count;
    for(int32 GuessWord=0;GuessWord<Guess.Len();GuessWord++)
    {
        if(Guess[GuessWord]== Hiddenword[GuessWord])
        {
            Count.Bulls++;
            continue;
        }
        for(int32 HiddenwordIndex=0;HiddenwordIndex<Guess.Len();HiddenwordIndex++)
        {
            if(Guess[GuessWord]==Hiddenword[HiddenwordIndex])
            {
                Count.Cows++;
                break;
            }
        }
    }
    return Count;
}