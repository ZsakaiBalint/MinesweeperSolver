#pragma once
#include <vector>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <string>
#include <gdiplus.h>

#include <fstream>
#include <winsock.h>

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

	void screenshotIsAlive(double screenScaling = 1.25);

	bool readIsAlive(std::string imageName = "", double screenScaling = 1.25, bool testMode = false);

	bool readIsWon(std::string imageName = "", double screenScaling = 1.25, bool testMode = false);

	void screenshotMinefield(double screenScaling = 1.25);

	std::vector<std::vector<Square>> readMinefield(std::string imageName = "",double screenScaling = 1.25, bool testMode = false);

	std::vector<std::pair<int, int>> getMinefieldDifference(std::vector<std::vector<Square>> prevMinefield, std::vector<std::vector<Square>> currentMinefield);

	void setPreviousMinefield(std::vector<std::vector<Square>> minefield);

	std::vector<std::vector<Square>> getPreviousMinefield();

	bool isMinefieldInitial(std::string imageName = "", double screenScaling = 1.25, bool testMode = false);

	double getScreenScaling();





	bool isValidIndex(int i, int j, int numRows, int numCols);

	std::vector<Square> getAdjacentElements(const std::vector<std::vector<Square>>& matrix, int row, int col);
};