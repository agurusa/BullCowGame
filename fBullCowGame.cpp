//
//  fBullCowGame.cpp
//  BullCowGame
//
//  Created by Aarthi Gurusami on 12/28/16.
//  Copyright © 2016 Aarthi Gurusami. All rights reserved.
//

#include "fBullCowGame.hpp"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

fBullCowGame::fBullCowGame(){
	Reset();
}

void fBullCowGame::Reset(){
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	MyMaxTries = MAX_TRIES;
	bGameIsWon = false;
    return;
}

int32 fBullCowGame::GetMaxTries() const {
    return MyMaxTries;
}

int32 fBullCowGame::GetCurrentTry() const {
    return MyCurrentTry;
}

int32 fBullCowGame::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}

bool fBullCowGame::IsLowercase(FString Word) const{
	if (Word.length() <=1){return true;}
	for (auto Letter : Word){
		if(!islower(Letter)){
            return false;
		}
	}
	return true;
}

bool fBullCowGame::IsIsogram(FString Word) const{
	if (Word.length() <=1){return true;}

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word){ 
		Letter = tolower(Letter);
		if (LetterSeen[Letter]){
			return false;
		}
		else{
			LetterSeen[Letter] = true;
		}
	}
	return true; //for example, in cases where /0 is entered.
}

EWordStatus fBullCowGame::CheckGuessValidity(FString Guess) const{
	if (!IsIsogram(Guess)){
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)){
		return EWordStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength()!= Guess.length()){
		return EWordStatus::Wrong_Length;
	}
	else{
    	return EWordStatus::Ok; 
	}
}

EGameStatus fBullCowGame::GameSummary() const{
	if (bGameIsWon){
		return EGameStatus::Won;
	}
	else{
		return EGameStatus::Lost;
	}
}

bool fBullCowGame::IsGameWon() const{
	return bGameIsWon;
}

// receives valid guess
// increments try number by 1
// returns count
fBullCowCount fBullCowGame::SubmitValidGuess(FString Guess){
	MyCurrentTry++;
	fBullCowCount BullCowCount;
	int32 HiddenWordLength = GetHiddenWordLength();
	for (int32 HWCharacter = 0; HWCharacter < HiddenWordLength; HWCharacter++){
		for (int32 GCharacter=0; GCharacter < HiddenWordLength; GCharacter++){
			if ( Guess[GCharacter] == MyHiddenWord[HWCharacter]){
				if (GCharacter == HWCharacter){
					BullCowCount.Bulls++;
				}
				else{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength){
		bGameIsWon = true;
	}
	else{
		bGameIsWon = false;
	}
	return BullCowCount;
}
