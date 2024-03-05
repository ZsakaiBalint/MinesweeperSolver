#include "guiData.h"

void GuiData::addLogMessage(std::string message) {
	logMessages.push_back(message);
}

void GuiData::setDifficulty(Difficulty difficulty) {
	this->difficulty = difficulty;
	int rows = difficulty.getHeight();
	int cols = difficulty.getWidth();
	paintableMatrix = std::vector<std::vector<PaintableSquare>>(rows, std::vector<PaintableSquare>(cols, PaintableSquare()));
	numberOfGuesses = 0;
	isWon = false;
}

void GuiData::addSquaresFromMemory(std::vector<std::vector<SquareState>> memoryMatrix) {

	//-1 or 0 or 1
	//the color must be semi-transparent

	for (unsigned i = 0; i < memoryMatrix.size(); ++i) {
		for (unsigned j = 0; j < memoryMatrix[i].size(); ++j) {

			switch(memoryMatrix[i][j]) {
				case UNOPENED:
					paintableMatrix[i][j] = PaintableSquare(-1, 100, 211, 211, 211);
					break;
				case MINEFREE:
					paintableMatrix[i][j] = PaintableSquare(0, 100, 0, 255, 0);
					break;
				case MINE:
					paintableMatrix[i][j] = PaintableSquare(1, 100, 255, 0, 0);
					break;
			}
			
		}
	}
}

void GuiData::addMinefreeSquares(std::vector<std::pair<int, int>> minefreeSquares) {
	for (unsigned i = 0; i < minefreeSquares.size(); ++i) {
		int row = minefreeSquares[i].first;
		int col = minefreeSquares[i].second;
		paintableMatrix[row][col] = PaintableSquare(0, 255, 0, 255, 0);
	}
}

void GuiData::addMineSquares(std::vector<std::pair<int, int>> mineSquares) {
	for (unsigned i = 0; i < mineSquares.size(); ++i) {
		int row = mineSquares[i].first;
		int col = mineSquares[i].second;
		paintableMatrix[row][col] = PaintableSquare(0, 255, 255, 0, 0);
	}
}

void GuiData::addGuesses(std::vector<std::vector<double>> guessMatrix) {

	//between 0 and 1
	//the color must be opaque

	for (unsigned i = 0; i < guessMatrix.size(); ++i) {
		for (unsigned j = 0; j < guessMatrix[i].size(); ++j) {

			double value = guessMatrix[i][j];
			int red, green;

			if (value == -1) {
				continue;
			}

			if (value < 0.5) {
				red = static_cast<int>(value * 2 * 255);  // Increase green from 0 to 255
				green = 255;
			}
			else {
				red = 255;
				green = static_cast<int>((1.0 - value) * 2 * 255);  // Decrease red from 255 to 0
			}
			

			paintableMatrix[i][j] = PaintableSquare(value, 255, red, green, 0);
		}
	}

	numberOfGuesses++;
}

std::vector<std::vector<PaintableSquare>> GuiData::getPaintableMatrix() {
	return this->paintableMatrix;
}

std::string GuiData::getLastLogMessage() {
	if (logMessages.size() == 0) {
		return "";
	}
	else {
		return logMessages.back();
	}
}

GuiData::GuiData(Difficulty difficulty) {
	this->difficulty = difficulty;
	int rows = difficulty.getHeight();
	int cols = difficulty.getWidth();
	paintableMatrix = std::vector<std::vector<PaintableSquare>>(rows, std::vector<PaintableSquare>(cols, PaintableSquare()));
	numberOfGuesses = 0;
	isWon = false;
}

GuiData::GuiData() {
	this->isWon = false;
	this->logMessages = std::vector<std::string>();
	this->paintableMatrix = std::vector<std::vector<PaintableSquare>>();
};

void GuiData::logSTEP1(std::vector<std::pair<int, int>> minefreeSquares, std::vector<std::pair<int, int>> mineSquares) {

	std::string newLogMessage = "";

	if (minefreeSquares.size() != 0) {
		newLogMessage += "Found minefree squares without constraints: ";
		for (unsigned i = 0; i < minefreeSquares.size(); ++i) {
			std::string first = std::to_string(minefreeSquares[i].first);
			std::string second = std::to_string(minefreeSquares[i].second);
			newLogMessage += "(" + first + "," + second + ")";
			( i == minefreeSquares.size() - 1 ) ? newLogMessage += "" : newLogMessage += ", ";
		}
	}

	if ( (minefreeSquares.size() != 0) && (mineSquares.size() != 0) ) {
		newLogMessage += " & ";
	}

	if (mineSquares.size() != 0) {
		newLogMessage += "Found mine squares without constraints: ";
		for (unsigned i = 0; i < mineSquares.size(); ++i) {
			std::string first = std::to_string(mineSquares[i].first);
			std::string second = std::to_string(mineSquares[i].second);
			newLogMessage += "(" + first + "," + second + ")";
			(i == mineSquares.size() - 1) ? newLogMessage += "" : newLogMessage += ", ";
		}
	}

	addLogMessage(newLogMessage);
}

void GuiData::logSTEP2(std::vector<std::pair<int, int>> minefreeSquares, std::vector<std::pair<int, int>> mineSquares, std::vector<ConstraintGroup> constraintGroups) {

	std::string newLogMessage = "";
	/*
	std::string newLogMessage = "ConstraintGroups: ";
	for (unsigned i = 0; i < constraintGroups.size(); ++i) {
		newLogMessage += "Group" + std::to_string(i + 1) + "=> ";
		newLogMessage += constraintGroups[i].toString();
	}
	*/

	if (minefreeSquares.size() != 0) {
		newLogMessage += "Found minefree squares with constraints: ";
		for (unsigned i = 0; i < minefreeSquares.size(); ++i) {
			std::string first = std::to_string(minefreeSquares[i].first);
			std::string second = std::to_string(minefreeSquares[i].second);
			newLogMessage += "(" + first + "," + second + ")";
			(i == minefreeSquares.size() - 1) ? newLogMessage += "" : newLogMessage += ", ";
		}
	}

	if ((minefreeSquares.size() != 0) && (mineSquares.size() != 0)) {
		newLogMessage += " & ";
	}

	if (mineSquares.size() != 0) {
		newLogMessage += "Found mine squares with constraints: ";
		for (unsigned i = 0; i < mineSquares.size(); ++i) {
			std::string first = std::to_string(mineSquares[i].first);
			std::string second = std::to_string(mineSquares[i].second);
			newLogMessage += "(" + first + "," + second + ")";
			(i == mineSquares.size() - 1) ? newLogMessage += "" : newLogMessage += ", ";
		}
	}

	addLogMessage(newLogMessage);
}

void GuiData::logSTEP3(std::vector<std::pair<int, int>> possibleGuesses, std::pair<int, int> chosenSquare, double bestProbability) {

	std::string newLogMessage = "Number of guesses: " + std::to_string(numberOfGuesses) + "; ";

	int percentage = static_cast<int>(bestProbability * 100);
	std::string percentageString = std::to_string(percentage);
	newLogMessage += "Found the best guesses with the probability of " + percentageString + "% of being a mine square : ";

	for (unsigned i = 0; i < possibleGuesses.size(); ++i) {
		std::string first = std::to_string(possibleGuesses[i].first);
		std::string second = std::to_string(possibleGuesses[i].second);
		newLogMessage += "(" + first + "," + second + "), ";
	}

	addLogMessage(newLogMessage);
}

int GuiData::getNumberOfGuesses() {
	return numberOfGuesses;
}