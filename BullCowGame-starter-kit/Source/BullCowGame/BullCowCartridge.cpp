// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Math/UnrealMathUtility.h"
#include "FileHelper.h"
#include "Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    TArray<FString> WordList;
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("HiddenWord.txt");
    FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
    Isograms = GetValidWords(WordList);
    SetUpGame();
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    
    if (bGameOver)
    {
        ClearScreen();
        SetUpGame();
    }
    else  //checking PlayerGuess
    {
        ProcessGuess(PlayerInput);
        
    }

}

void UBullCowCartridge::SetUpGame()
{
    //Welcoming the player
    PrintLine(TEXT("Welcome To Bulls and Cows"));
    HiddenWord = Isograms[FMath::RandRange(0,Isograms.Num()-1)];
    Lives = HiddenWord.Len();
    bGameOver = false;
  
    PrintLine(TEXT("Guess the %i letter word"),HiddenWord.Len());
    PrintLine(TEXT("Your Total Lives are: %i"),Lives);
    PrintLine(TEXT("Type in your guess.\nPress Enter To Continue..."));
    PrintLine(TEXT("The Hidden Word is:- %s. \nIt is %i characters long!"),*HiddenWord, HiddenWord.Len()); 
       
}

void UBullCowCartridge::EndGame()
{
    bGameOver=true;
    
    PrintLine(TEXT("\nPress Enter TO Play Again."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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
        FBullCowCount Score = GetBullCows(Guess);

        PrintLine(TEXT("You have %i Bulls and %i Cows"),Score.Bulls,Score.Cows);

        PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for(int32 Index=0;Index<Word.Len();Index++)
    {
        for (int32 Comparison = Index+1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index]==Word[Comparison])
            {
                return false;
            }
        }
        
    }
    return true;

}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for (FString Word : WordList)
    {
        if(Word.Len() >= 4 && Word.Len() <=8 && IsIsogram(Word))   
        {
            
            ValidWords.Emplace(Word);
            
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const 
{
    FBullCowCount Count;
    // For every index guess is same as index of the hidden word, BullCount++
    // If not a bull was it a cow? if yes CowCount++

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len() ; GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
           if (Guess[GuessIndex]==HiddenWord[HiddenIndex])
           {
               Count.Cows++;
               break;
           }
           
        }
        
        
        
    }
    return Count;    
}