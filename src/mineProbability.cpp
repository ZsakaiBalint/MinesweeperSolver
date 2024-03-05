#include "mineProbability.h"
#include <iostream>

MineProbability::MineProbability(Difficulty difficulty, MinefieldMemory* minefieldMemory): difficulty(difficulty) {
	this->minefieldMemory = minefieldMemory;
	clearMatrix();
};

void MineProbability::addSolutionMatrix(const SolutionMatrix& matrix) {
	std::vector<std::pair<int, int>> allVariables = matrix.getAllVariables();
	std::vector<std::vector<int>> allValues = matrix.getAllValues();

	//iterate through the columns
	for (unsigned i = 0; i < allValues[0].size(); ++i) {

		//add together the values in that column
		double sum = 0;
		for (unsigned j = 0; j < allValues.size(); ++j) {
			sum += allValues[j][i];
		}

		double newProbability = sum / allValues.size();
		int row = allVariables[i].first;
		int col = allVariables[i].second;
		probabilityMatrix[row][col].first = newProbability;
	}
};

void MineProbability::addKnownSquares() {
	std::vector<std::vector<SquareState>> memory = minefieldMemory->getMemoryMatrix();
	for (unsigned i = 0; i < memory.size(); ++i) {
		for (unsigned j = 0; j < memory[i].size(); ++j) {

			if (memory[i][j] == MINEFREE || memory[i][j] == MINE) {
				probabilityMatrix[i][j].first = -1;
			}

		}
	}
};

void MineProbability::calculateUnknownSquares() {

	double remainingMines = difficulty.getNumberOfMines();
	double remainingSquares = 0;
	
	for (unsigned i = 0; i < probabilityMatrix.size(); ++i) {
		for (unsigned j = 0; j < probabilityMatrix[i].size(); ++j) {

			if ( probabilityMatrix[i][j].first == -2 ) {
				remainingSquares++;
			}
			else if ( probabilityMatrix[i][j].first > 0 ) {
				remainingMines -= probabilityMatrix[i][j].first;
			}

		}
	}

	double remainingProbabilities = remainingMines / remainingSquares;
	remainingProbabilities = std::round(remainingProbabilities * 1000.0) / 1000.0; //round the probabilites to 3 decimal places

	for (unsigned i = 0; i < probabilityMatrix.size(); ++i) {
		for (unsigned j = 0; j < probabilityMatrix[i].size(); ++j) {

			if (probabilityMatrix[i][j].first == -2) {
				probabilityMatrix[i][j].first = remainingProbabilities;
			}

		}
	}

};

std::vector<std::vector<double>> MineProbability::getProbabilityMatrix() const {
	std::vector<std::vector<double>> matrixWithoutSquareLocations;

	for (unsigned i = 0; i < probabilityMatrix.size(); ++i) {
		std::vector<double> newRow;
		for (unsigned j = 0; j < probabilityMatrix[i].size(); ++j) {
			newRow.push_back(probabilityMatrix[i][j].first);
		}
		matrixWithoutSquareLocations.push_back(newRow);
	}
	return matrixWithoutSquareLocations;
};

void MineProbability::clearMatrix() {

	probabilityMatrix.clear();

	int rows = difficulty.getHeight();
	int cols = difficulty.getWidth();
	// Initialize probabilityMatrix with the correct size
	this->probabilityMatrix = std::vector<std::vector<std::pair<double, SquareLocation>>>(rows, std::vector<std::pair<double, SquareLocation>>(cols));

	for (unsigned i = 0; i < rows; ++i) {

		//std::vector<std::pair<double, SquareLocation>> newRow = std::vector<std::pair<double, SquareLocation>>();

		for (unsigned j = 0; j < cols; ++j) {

			//std::pair<double, SquareLocation> newPair;

			if ((i == 0 && j == 0) ||				 // Top-left corner
				(i == 0 && j == cols - 1) ||		 // Top-right corner
				(i == rows - 1 && j == 0) ||		 // Bottom-left corner
				(i == rows - 1 && j == cols - 1))	 // Bottom-right corner
			{
				//newPair = { -2,CORNER };
				this->probabilityMatrix[i][j] = { -2,CORNER };
				//newPair.first = -2.0;
				//newPair.second = SquareLocation::CORNER;

			}

			else if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {	//edge element
				//newPair = { -2, EDGE };
				this->probabilityMatrix[i][j] = { -2,EDGE };
				//newPair.first = -2.0;
				//newPair.second = SquareLocation::EDGE;
			}

			else {			//internal element
				//newPair = { -2, INTERNAL };
				this->probabilityMatrix[i][j] = { -2,INTERNAL };
				//newPair.first = -2.0;
				//newPair.second = SquareLocation::INTERNAL;
			}

			//newRow.push_back(newPair);

		}

		//probabilityMatrix[i] = newRow;

	}
};

std::vector<std::pair<int, int>> MineProbability::getMineSquares() {

	std::vector<std::pair<int, int>> mineSquares = std::vector<std::pair<int, int>>();

	for (unsigned i = 0; i < probabilityMatrix.size(); ++i) {
		for (unsigned j = 0; j < probabilityMatrix[i].size(); ++j) {
			if (probabilityMatrix[i][j].first == 1) {
				mineSquares.push_back({i,j});
			}
		}
	}

	return mineSquares;
};

std::vector<std::pair<int, int>> MineProbability::getMinefreeSquares() {

	std::vector<std::pair<int, int>> minefreeSquares = std::vector<std::pair<int, int>>();

	for (unsigned i = 0; i < probabilityMatrix.size(); ++i) {
		for (unsigned j = 0; j < probabilityMatrix[i].size(); ++j) {
			if (probabilityMatrix[i][j].first == 0) {
				minefreeSquares.push_back({ i,j });
			}
		}
	}

	return minefreeSquares;
};

std::vector<std::pair<int, int>> MineProbability::getBestGuesses() {

	std::vector<std::pair<int, int>> bestGuesses = std::vector<std::pair<int, int>>();
	std::pair<double, SquareLocation> currentValue = { 1,INTERNAL };

	for (unsigned i = 0; i < probabilityMatrix.size(); ++i) {
		for (unsigned j = 0; j < probabilityMatrix[i].size(); ++j) {

			if ( probabilityMatrix[i][j] < currentValue && probabilityMatrix[i][j].first != -1 ) {
				currentValue = probabilityMatrix[i][j];
				bestGuesses.clear();
				bestGuesses.push_back({ i,j });
			}
			else if ( probabilityMatrix[i][j] == currentValue ) {
				bestGuesses.push_back({ i,j });
			}

		}
	}

	return bestGuesses;
};

double MineProbability::getBestProbability() {

	double bestProbability = 1;

	for (unsigned i = 0; i < probabilityMatrix.size(); ++i) {
		for (unsigned j = 0; j < probabilityMatrix[i].size(); ++j) {

			double currentProbability = probabilityMatrix[i][j].first;
			if (currentProbability < bestProbability && currentProbability != -1) {
				bestProbability = currentProbability;
			}

		}
	}

	return bestProbability;
}

bool operator<(const std::pair<double, SquareLocation>& lhs, const std::pair<double, SquareLocation>& rhs) {
	if (lhs.first < rhs.first) { return true; }
	else if (lhs.first == rhs.first) { return lhs.second < rhs.second; }
};

bool operator==(const std::pair<double, SquareLocation>& lhs, const std::pair<double, SquareLocation>& rhs) {
	return (lhs.first == rhs.first) && (lhs.second == rhs.second);
};