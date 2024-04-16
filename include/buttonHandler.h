#pragma once
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "difficulty.h"
#include "screenReader.h"
#include "mineProbability.h"
#include "clicker.h"
#include "constraintMaker.h"
#include "constraintGroupSolver.h"
#include "guiData.h"
#include "fileWriter.h"

class ButtonHandler {
private:
	Difficulty difficulty;
	HWND minesweeperHandle;
	GuiData* guiData;
	MinefieldMemory* minefieldMemory;
	MineProbability* mineProbability;
	ScreenReader* screenReader;
	Clicker* clicker;

	std::vector<ConstraintGroup> constraintGroups;

public:
	ButtonHandler();
	~ButtonHandler();
	void setDifficulty(Difficulty difficulty);
	void setMinesweeperHandle(HWND handle);
	void setGuiData(GuiData* guiData);

	void getResultsWithoutConstraints();
	void getSureResultsWithConstraints();
	void makeGuessWithConstraints();

	double getScreenScaling();

	void step();
	bool execute();
	void test();

	std::vector<std::vector<PaintableSquare>> getPaintableMatrix();
	std::string getLastLogMessage();

	int substepNumber;
};