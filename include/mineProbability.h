#pragma once
#include <vector>
#include "difficulty.h"
#include "minefieldMemory.h"
#include "solutionMatrix.h"


enum SquareLocation {
	CORNER,
	EDGE,
	INTERNAL
};

class MineProbability {
private:
	Difficulty difficulty;
	MinefieldMemory* minefieldMemory;
	std::vector<std::vector<std::pair<double,SquareLocation>>> probabilityMatrix;
public:
	MineProbability(Difficulty difficulty, MinefieldMemory* minefieldMemory);
	void addSolutionMatrix(const SolutionMatrix& matrix);
	void addKnownSquares();
	void calculateUnknownSquares();
	std::vector<std::vector<double>> getProbabilityMatrix() const;
	void clearMatrix();
	std::vector<std::pair<int, int>> getMineSquares();
	std::vector<std::pair<int, int>> getMinefreeSquares();
	std::vector<std::pair<int, int>> getBestGuesses();
	double getBestProbability();
	friend bool operator<(const std::pair<double, SquareLocation>& lhs, const std::pair<double, SquareLocation>& rhs);
	friend bool operator==(const std::pair<double, SquareLocation>& lhs, const std::pair<double, SquareLocation>& rhs);
};