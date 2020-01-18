// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetUpGame();

    PrintLine(TEXT("The Hidden Word is:- %s. \nIt is %i characters long!"),*HiddenWord, HiddenWord.Len()); 
  
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
    }
    else  //checking PlayerGuess
    {
        ProcessGuess(Input);
        
    }

}

void UBullCowCartridge::SetUpGame()
{
    //Welcoming the player
    PrintLine(TEXT("Welcome To Bulls and Cows"));

    HiddenWord=TEXT ("jos");  
    Lives = HiddenWord.Len();
    bGameOver = false;
  
    PrintLine(TEXT("Guess the %i letter word"),HiddenWord.Len());
    PrintLine(TEXT("Your Total Lives are: %i"),Lives);
    PrintLine(TEXT("Type in your guess.\nPress Enter To Continue..."));

   
}

void UBullCowCartridge::EndGame()
{
    bGameOver=true;
    
    PrintLine(TEXT("\nPress Enter TO Play Again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
        if(HiddenWord==Guess)
        {
            PrintLine(TEXT("You have won!"));
            EndGame();
            return;
        }

        if (Guess.Len() != HiddenWord.Len())
        {
            PrintLine(TEXT("The HIdden word is %i letters long"), HiddenWord.Len());
            PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);
            return;

        }

        // //Check if isogram
        if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("No repeating letters, guess again"));
            return;
        }
        //Prompt to guess again

        //Remove Life
        PrintLine(TEXT("Lost a life!"));
        --Lives;

        if (Lives <= 0)
        {
            ClearScreen();
            PrintLine(TEXT("You have no lives left!"));
            PrintLine(TEXT("The Hidden Word was: %s"), *HiddenWord);
            EndGame();
            return;
        }
        
        //Show the players the bulls and cows
        PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{


    for(int32 Index=0,Comparison=Index+1;Comparison<Word.Len();Comparison++)
    {
        if(Word[Index]==Word[Comparison])
        {
            return false;
        }
    }
    // For each letter
    // start at element [0]
    // compare against the next letter.
    // until we reach [Word.len()-1]
    //if any letters are same return false
    
   return true;

}