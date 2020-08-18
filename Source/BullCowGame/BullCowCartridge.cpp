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
    
    HiddenWord = TEXT("cmasmas");
    Lives = HiddenWord.Len();
    bGameOver = false;
    
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
         if (Guess == HiddenWord)
        {
            PrintLine(TEXT("You have won"));
            EndGame();
        } 
        else 
        {
            PrintLine(TEXT("You have lost a life."));
            PrintLine(TEXT("%i"), --Lives);
            if (Lives > 0) 
            {
                if (Guess.Len() != HiddenWord.Len()) 
                {
                    PrintLine(TEXT("Sorry, try again. \n You have %i lives remaining."), Lives);
                }
            
            } else 
            {
                PrintLine(TEXT("You have no lives left."));
                EndGame();
            }
        }
}