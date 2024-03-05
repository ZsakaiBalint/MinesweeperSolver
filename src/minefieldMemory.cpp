#include "minefieldMemory.h"

void MinefieldMemory::markAsMinefree(std::vector<std::pair<int, int>> squares) {
	for (unsigned i = 0; i < squares.size(); ++i) {

		if (memoryMatrix[squares[i].first][squares[i].second] == UNOPENED){
			memoryMatrix[squares[i].first][squares[i].second] = MINEFREE;
		}

	}
}

void MinefieldMemory::markAsMine(std::vector<std::pair<int, int>> squares) {
	for (unsigned i = 0; i < squares.size(); ++i) {

		if (memoryMatrix[squares[i].first][squares[i].second] == UNOPENED) {
			memoryMatrix[squares[i].first][squares[i].second] = MINE;
		}

		
	}
	knownMines += squares.size();
}

bool MinefieldMemory::isOpened(std::pair<int, int> square) {
	return memoryMatrix[square.first][square.second] != UNOPENED;
}

bool MinefieldMemory::isMinefree(std::pair<int, int> square) {
	return memoryMatrix[square.first][square.second] == MINEFREE;
}

bool MinefieldMemory::isMine(std::pair<int, int> square) {
	return memoryMatrix[square.first][square.second] == MINE;
}

MinefieldMemory::MinefieldMemory(Difficulty difficulty) {
	int rows = difficulty.getHeight();
	int cols = difficulty.getWidth();
	memoryMatrix = std::vector<std::vector<SquareState>> (rows, std::vector<SquareState>(cols, UNOPENED));
	knownMines = 0;
}

std::vector<std::vector<SquareState>> MinefieldMemory::getMemoryMatrix() const {
	return this->memoryMatrix;
}

int MinefieldMemory::getKnownMines() {
	return knownMines;
}