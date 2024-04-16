#pragma once
#include <string>
#include <vector>
#include "difficulty.h"
#include "minefieldMemory.h"
#include "constraintGroup.h"

struct PaintableSquare {
	double value;
	int alpha;
	int red;
	int green;
	int blue;

	PaintableSquare(double v, int a, int r, int g, int b) {
		value = v;
		alpha = a;
		red = r;
		green = g;
		blue = b;
	}

	//grey
	PaintableSquare() {
		value = -1;
		alpha = 255;
		red = 211;
		green = 211;
		blue = 211;
	}
};

class GuiData {
private:
	std::vector<std::vector<PaintableSquare>> paintableMatrix;
	std::vector<std::string> logMessages;
	Difficulty difficulty;
	int numberOfGuesses;

public:
	bool isWon;

	void addLogMessage(std::string message);
	void logSTEP1(std::vector<std::pair<int, int>> minefreeSquares, std::vector<std::pair<int, int>> mineSquares);
	void logSTEP2(std::vector<std::pair<int, int>> minefreeSquares, std::vector<std::pair<int, int>> mineSquares, std::vector<ConstraintGroup> constraintGroups);
	void logSTEP3(std::vector<std::pair<int, int>> possibleGuesses, std::pair<int,int> chosenSquare, double bestProbability);

	void setDifficulty(Difficulty difficulty);
	void addSquaresFromMemory(std::vector<std::vector<SquareState>> memoryMatrix);

	void addMinefreeSquares(std::vector<std::pair<int, int>> minefreeSquares);
	void addMineSquares(std::vector<std::pair<int, int>> mineSquares);

	void addGuesses(std::vector<std::vector<double>> guessMatrix);
	std::vector<std::string> getLogMessages();
	std::string getLastLogMessage();
	std::vector<std::vector<PaintableSquare>> getPaintableMatrix();
	GuiData(Difficulty difficulty);
	GuiData();
	int getNumberOfGuesses();
};