
/* this is the console executable, that amkes use of the BullCow class. 
This acts as the view in an MVC pattern, and is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/
//
//  main.cpp
//  BullCowGame
//
//  Created by Aarthi Gurusami on 12/27/16.
//  Copyright © 2016 Aarthi Gurusami. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include "fBullCowGame.hpp"

// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
void PrintGuess();

// instantiate a new game
fBullCowGame BCGame; 



void PrintIntro(){
    std::cout << "Welcome to Bulls and Cows" << std::endl;
    std::cout << "Guess the "<< BCGame.GetHiddenWordLength();
    std::cout << " letter isogram that I'm thinking of!!" << std::endl;
    return;
}

FText GetValidGuess(){
    EWordStatus Status = EWordStatus::Invalid_Status;
    FText Guess = "";
    do{
        int32 currentTry = BCGame.GetCurrentTry();
        std::cout << "Try " << currentTry << " out of " << BCGame.GetMaxTries();
        std::cout << ": Enter your guess: ";
        getline (std::cin, Guess);
        Status = BCGame.CheckGuessValidity(Guess); 
        switch (Status){
            case EWordStatus::Not_Isogram:
                std::cout<< "Please enter a word that is an isogram.\n";
                break;
            case EWordStatus::Wrong_Length:
                std::cout<< "Please enter a word that is " << BCGame.GetHiddenWordLength() << " letters long.\n";
                break;
            case EWordStatus::Not_Lowercase:
                std::cout<< "Please enter your word in all lowercase letters.\n";
                break;
            default:
                break;
        }
    } while(Status != EWordStatus::Ok);
    return Guess;
}

void PrintGameSummary(){
    EGameStatus Status = BCGame.GameSummary();
    switch (Status){
        case EGameStatus::Won:
            std::cout << "Congrats you won!\n";
            break;
        case EGameStatus::Lost:
            std::cout << "Boo you lost.\n";
            break;
        default:
            break;
    }
    return;
}

void PrintGuess(FText Guess){
    std::cout << "your guess was: " << Guess << std::endl;

}

void PlayGame(){
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        FText Guess = GetValidGuess(); 
        fBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        PrintGuess(Guess);
        std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
        std::cout << "Cows = " << BullCowCount.Cows << std::endl;
    }
    PrintGameSummary();
    return;    
}

bool AskToPlayAgain(){
    std::cout << "Do you want to play again? Y/N\n";
    FText Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'Y') || (Response[0] == 'y');
}


int main(int argc, const char * argv[]) {
    bool bPlayAgain = false;
    do{
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while(bPlayAgain);
}
