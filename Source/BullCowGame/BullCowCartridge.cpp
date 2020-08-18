// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
    
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);
    // PrintLine(FString::Printf(TEXT("The HiddenWord is: %s"), *HiddenWord));    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver) 
    {
        ClearScreen();
        SetupGame();
    } else 
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to Bull Cow Game"));
    
    HiddenWord = TEXT("caprend");
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
         if (Guess == HiddenWord)
        {
            PrintLine(TEXT("You have won"));
            EndGame();
            return;
        } 

        if (Guess.Len() != HiddenWord.Len()) 
        {
            PrintLine(TEXT("Sorry, try again. \n You have %i lives remaining."), Lives);
            PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
            return;
        }

        if (!IsIsogram(Guess))
        {

            PrintLine(TEXT("No repeating letters, guess again."));
            return;
        }

        PrintLine(TEXT("You have lost a life."));
        --Lives;

        if (Lives <= 0)  
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives left."));
            PrintLine(TEXT("The hidden word was %s"), *HiddenWord);
            EndGame();
            return;
        }

        PrintLine(TEXT("Guess again. You have %i lives left."), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
// bool UBullCowCartridge::IsIsogram(FString Word)
{
    for (int32 Index = 0;  Index < Word.Len(); Index++) 
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison]) 
            {
                return false;
            }
        }

    }

    return true;
}