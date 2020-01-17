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
        
        if(HiddenWord==Input)
        {
            PrintLine(TEXT("You have won!"));
            EndGame();
        }
        else
        {       
            if(Input.Len() != HiddenWord.Len())
            {
                PrintLine(TEXT("The hidden word is %i characters long. \nYou have Lost!"),HiddenWord.Len());
            EndGame();
            }
            else
            {
                --Lives;
                PrintLine(TEXT("Lost a Life!"));
                if(Lives>0)
                {
                
                    PrintLine(TEXT("Your Guess is incorrect! \nYour remaining Lives are: %i"),Lives);
                }
                else
                {
                    PrintLine(TEXT("You have no lives left!"));
                    EndGame();
                }
                
            }
            
        }
    }

    //Check if isogram
    //Prompt to guess again

    //Check right no of characters
    //Prompt to guess again

    //Remove Life
    //Check if  lives>0
    //If yes GuessAgain
    //Show Lives Left
    //if no show GameOver and the HiddenWord
    //Prompt to play again, Press Enter to Play Again?
    //Check user input
    //PlayAgain or quit
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
    PrintLine(TEXT("Press Enter TO Play Again."));
}