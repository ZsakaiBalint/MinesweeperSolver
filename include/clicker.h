#pragma once
#include <chrono>
#include <thread>

#include "Windows.h"
#include "difficulty.h"

class Clicker {
private:
	Difficulty difficulty;
	HWND minesweeperHandle;
public:
	Clicker(Difficulty difficulty,HWND minesweeperHandle) : difficulty(difficulty), minesweeperHandle(minesweeperHandle) {};
	void moveCursorAndClick(int rowIndex, int colIndex) const;
	void moveCursorAndFlag(int rowIndex, int colIndex) const;
	void moveCursorAndClickNewGame() const;
};
