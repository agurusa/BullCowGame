/*
The game logic (no view code or direct user interaction)
The game is a simple guess the wrod game bsaed on MasterMind.
*/
//
//  fBullCowGame.hpp
//  BullCowGame
//
//  Created by Aarthi Gurusami on 12/28/16.
//  Copyright © 2016 Aarthi Gurusami. All rights reserved.
//


#pragma once

#ifndef fBullCowGame_hpp
#define fBullCowGame_hpp

#include <stdio.h>
#include <string>

// Make unreal friendly
using FString = std::string;
using int32 = int;

#endif /* fBullCowGame_hpp */

struct fBullCowCount{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus{
	Invalid_Status,
	Ok,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

enum class EGameStatus{
	Won,
	Lost
};

class fBullCowGame{
public:
	fBullCowGame(); //constructor 
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    EWordStatus CheckGuessValidity(FString) const;
    EGameStatus GameSummary() const;
    bool IsGameWon() const;
    
    void Reset();

    fBullCowCount SubmitValidGuess(FString);
private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
