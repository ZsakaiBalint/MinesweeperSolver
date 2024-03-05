#pragma once
#include <fstream>

#include "difficulty.h"

class FileWriter {
public:
	void saveResult(Difficulty difficulty, int numberOfGuesses, bool isWon);
};