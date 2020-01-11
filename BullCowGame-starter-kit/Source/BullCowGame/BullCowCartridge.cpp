// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome To Bulls and Cows"));
    PrintLine(TEXT("Guess the 3 letter word"));
    PrintLine(TEXT("Press Enter To Continue"));
    HiddenWord=TEXT ("jos");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    if(HiddenWord==Input)
    {
        PrintLine(TEXT("Your guess is right"));
    }
    else
    {
        PrintLine(TEXT("Try again"));
    }
    
}