#pragma once
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <string>

#include "minefieldMemory.h"

enum Square {
	UNKNOWN = -2,
	FLAGGED = -1,
	ZERO = 0,
	ONE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8
};

class ScreenReader {
private: 
	Difficulty difficulty;
	HWND minesweeperHandle;
	std::vector<std::vector<Square>> previousMinefield;

public:
	ScreenReader(Difficulty difficulty, HWND minesweeperHandle);

	void screenshotIsAlive();

	bool readIsAlive(std::string imageName = "",bool testMode = false);

	bool readIsWon(std::string imageName = "",bool testMode = false);

	void screenshotMinefield();

	std::vector<std::vector<Square>> readMinefield(std::string imageName = "",bool testMode = false);

	std::vector<std::pair<int, int>> getMinefieldDifference(std::vector<std::vector<Square>> prevMinefield, std::vector<std::vector<Square>> currentMinefield);

	void setPreviousMinefield(std::vector<std::vector<Square>> minefield);

	std::vector<std::vector<Square>> getPreviousMinefield();

	bool isMinefieldInitial(std::string imageName = "",bool testMode = false);
};