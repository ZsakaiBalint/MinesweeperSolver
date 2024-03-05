#pragma once
#include <vector>
#include "difficulty.h"

enum SquareState {
	UNOPENED = -1,
	MINEFREE = 0,
	MINE = 1
};

class MinefieldMemory {
private:
	std::vector<std::vector<SquareState>> memoryMatrix;
	int knownMines;
public:
	void markAsMinefree(std::vector<std::pair<int,int>> squares);
	void markAsMine(std::vector<std::pair<int, int>> squares);
	bool isOpened(std::pair<int, int> square);
	bool isMinefree(std::pair<int, int> square);
	bool isMine(std::pair<int, int> square);
	std::vector<std::vector<SquareState>> getMemoryMatrix() const;
	MinefieldMemory(Difficulty difficulty);
	int getKnownMines();
};