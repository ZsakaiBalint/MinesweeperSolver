#include "buttonHandler.h"

ButtonHandler::~ButtonHandler() {
	delete this->minefieldMemory;
	delete this->mineProbability;
	delete this->screenReader;
	delete this->clicker;
	delete this->guiData;
}

void ButtonHandler::setDifficulty(Difficulty difficulty) {

	this->difficulty = difficulty;													
	delete this->screenReader;														
	this->screenReader = new ScreenReader(difficulty,minesweeperHandle);

	std::string minefieldImageLocation = "minesweeper_screenshot.png";
	double screenScaling = screenReader->getScreenScaling();

	screenReader->screenshotMinefield(screenScaling);
	bool isInitial = screenReader->isMinefieldInitial(minefieldImageLocation,screenScaling);
	if (!isInitial) { return; }														
	
	//only do the following part if the user started a new game
	delete this->minefieldMemory;
	delete this->mineProbability;
	delete this->clicker;
	delete this->guiData;

	this->minefieldMemory = new MinefieldMemory(difficulty);
	this->mineProbability = new MineProbability(difficulty, this->minefieldMemory);
	this->clicker = new Clicker(difficulty,minesweeperHandle);
	this->guiData = new GuiData(difficulty);
	
	substepNumber = 1;
};

void ButtonHandler::step() {

	do {
		switch (substepNumber) {
		case 1:
			getResultsWithoutConstraints();
			break;
		case 2:
			getSureResultsWithConstraints();
			break;
		case 3:
			makeGuessWithConstraints();
			break;
		}
	} while (substepNumber != 1);

};

bool ButtonHandler::execute() {

	std::string isAliveImageLocation = "isalive_screenshot.png";
	double screenScaling = screenReader->getScreenScaling();

	this->screenReader->screenshotIsAlive(screenScaling);
	bool isAlive = this->screenReader->readIsAlive(isAliveImageLocation, screenScaling);

	if (!isAlive) { return false; }

	while (isAlive) {
		step();
		this->screenReader->screenshotIsAlive(screenScaling);
		isAlive = this->screenReader->readIsAlive(isAliveImageLocation, screenScaling);
	}

	//save if we won or lost
	this->screenReader->screenshotIsAlive(screenScaling);
	std::string isWonImageLocation = "isalive_screenshot.png";
	guiData->isWon = this->screenReader->readIsWon(isWonImageLocation, screenScaling);

	return true;
};

void ButtonHandler::test() {
	
	int numberOfTests = 100;
	for (int i = 0; i < numberOfTests; ++i) {

		//first, solve the current minesweeper game
		bool canExecute = execute();

		//then write the results into a file
		if (canExecute) {
			FileWriter fw;
			fw.saveResult(difficulty, guiData->getNumberOfGuesses(), guiData->isWon);
		}

		clicker->moveCursorAndClickNewGame();

		//all objects need to be reset
		Difficulty currentDifficulty = this->difficulty;
		setDifficulty(difficulty);
	}
	
};

void ButtonHandler::getResultsWithoutConstraints() {
	//SUBSTEP 1 => SCREENREADER + CONSTRAINTMAKER

	double screenScaling = screenReader->getScreenScaling();

	//check if we are alive
	this->screenReader->screenshotIsAlive(screenScaling);
	std::string isAliveImageLocation = "isalive_screenshot.png";

	bool isAlive = this->screenReader->readIsAlive(isAliveImageLocation,screenScaling);
	if (!isAlive) { return; }

	//read the new minefield
	screenReader->screenshotMinefield(screenScaling);
	std::string minefieldImageLocation = "minesweeper_screenshot.png";
	std::vector<std::vector<Square>> newMinefield = this->screenReader->readMinefield(minefieldImageLocation,screenScaling);


	//DEBUG
	//for cases when there is no mines left and there are still 
	//minefree squares unprobed, which are enclosed with mines and walls
	int remainingMines = difficulty.getNumberOfMines() - minefieldMemory->getKnownMines();
	if (remainingMines == 0) {
		for (unsigned i = 0; i < newMinefield.size(); ++i) {
			for (unsigned j = 0; j < newMinefield[i].size(); ++j) {
				if (newMinefield[i][j] == UNKNOWN) { clicker->moveCursorAndClick(i, j); }
			}
		}
		substepNumber = 1;
		return;
	}


	//check the difference between the old and new minefield
	std::vector<std::vector<Square>> oldMinefield = this->screenReader->getPreviousMinefield();
	std::vector<std::pair<int, int>> differences = this->screenReader->getMinefieldDifference(oldMinefield, newMinefield);

	//save the new minefield
	this->screenReader->setPreviousMinefield(newMinefield);

	//save all the freshly uncovered squares, which are all minefree
	this->minefieldMemory->markAsMinefree(differences);

	//after saving the freshly uncovered squares, display everything in minefieldmemory as semi-transparent
	this->guiData->addSquaresFromMemory(minefieldMemory->getMemoryMatrix());

	//create a constraintmaker
	ConstraintMaker constraintMaker(newMinefield);

	//get the squares that can be solved without constraints
	//do this with both mine and minefree squares
	std::vector<std::pair<int, int>> minefreeWithoutConstraints = constraintMaker.calculateMinefreeSquares(newMinefield);

	//we want to display the minefree squares as opaque green
	this->guiData->addMinefreeSquares(minefreeWithoutConstraints);

	//save them
	this->minefieldMemory->markAsMinefree(minefreeWithoutConstraints);
	//click on them
	for (unsigned i = 0; i < minefreeWithoutConstraints.size(); ++i) {
		this->clicker->moveCursorAndClick(minefreeWithoutConstraints[i].first, minefreeWithoutConstraints[i].second);
	}
	std::vector<std::pair<int, int>> mineWithoutConstraints = constraintMaker.calculateMineSquares(newMinefield);

	//we want to display these squares as opaque red
	this->guiData->addMineSquares(mineWithoutConstraints);

	this->minefieldMemory->markAsMine(mineWithoutConstraints);
	for (unsigned i = 0; i < mineWithoutConstraints.size(); ++i) {
		this->clicker->moveCursorAndFlag(mineWithoutConstraints[i].first, mineWithoutConstraints[i].second);
	}

	//save the constraint groups in case we need to proceed to SUBSTEP 2
	constraintGroups = constraintMaker.getConstraintGroups();

	//if we got new information by probing these squares, repeat this substep
	if ((minefreeWithoutConstraints.size() != 0) || (mineWithoutConstraints.size() != 0)) { 
		substepNumber = 1;


		//log the results
		this->guiData->logSTEP1(minefreeWithoutConstraints,mineWithoutConstraints);
	}
	else {
		substepNumber = 2;
	}
}

void ButtonHandler::getSureResultsWithConstraints() {
	//SUBSTEP 2 => ConstraintMaker + ConstraintGroupSolver + MineProbability

	//check how many constraintgroups we got
	int numberOfConstraintGroups = constraintGroups.size();

	//solve each constraintgroup and get the results
	std::vector<SolutionMatrix> solutionMatrices = std::vector<SolutionMatrix>();
	for (int i = 0; i < numberOfConstraintGroups; ++i) {
		ConstraintGroup constraintGroup = constraintGroups[i];
		ConstraintGroupSolver constraintGroupSolver(constraintGroup);
		constraintGroupSolver.solve();
		SolutionMatrix solution = constraintGroupSolver.getSolutionMatrix();
		solutionMatrices.push_back(solution);
	}

	//create a solution from the matrices and the information from the minefieldmemory
	for (int i = 0; i < solutionMatrices.size(); ++i) {
		this->mineProbability->addSolutionMatrix(solutionMatrices[i]);
	}

	//get the sure results
	std::vector<std::pair<int, int>> mineSquares = this->mineProbability->getMineSquares();
	std::vector<std::pair<int, int>> minefreeSquares = this->mineProbability->getMinefreeSquares();

	//save them
	this->minefieldMemory->markAsMine(mineSquares);
	this->minefieldMemory->markAsMinefree(minefreeSquares);

	//calculate the remaining probabilities
	this->mineProbability->addKnownSquares();
	this->mineProbability->calculateUnknownSquares();

	//execute the sure results
	for (unsigned i = 0; i < mineSquares.size(); ++i) {
		this->clicker->moveCursorAndFlag(mineSquares[i].first, mineSquares[i].second);
	}
	for (unsigned i = 0; i < minefreeSquares.size(); ++i) {
		this->clicker->moveCursorAndClick(minefreeSquares[i].first, minefreeSquares[i].second);
	}

	//we want to display mine squares as opaque red
	this->guiData->addMineSquares(mineSquares);
	//and display minefree squares as opaque green
	this->guiData->addMinefreeSquares(minefreeSquares);



	//in case we uncover any new information go back to SUBSTEP 1
	if (mineSquares.size() != 0 || minefreeSquares.size() != 0) {
		substepNumber = 1;
		this->mineProbability->clearMatrix();
		this->guiData->logSTEP2(minefreeSquares, mineSquares, constraintGroups);
	}
	else {
		substepNumber = 3;
	}

	//clear the constraint groups
	constraintGroups.clear();
}

void ButtonHandler::makeGuessWithConstraints() {
	//SUBSTEP 3 => MineProbability

	//in case we didn't uncover any new information, make a guess
	std::vector<std::pair<int, int>> possibleGuesses = mineProbability->getBestGuesses();
	int random = rand() % possibleGuesses.size();
	std::pair<int, int> guess = possibleGuesses[random];

	//save this guess 
	//(here we put it into a vector because the "markAsMine" function's parameter has to be a vector)
	std::vector<std::pair<int, int>> newGuess = std::vector<std::pair<int, int>>();
	newGuess.push_back(guess);
	this->minefieldMemory->markAsMinefree(newGuess);

	//execute the guess
	this->clicker->moveCursorAndClick(guess.first, guess.second);

	//display all probabilities with colorful squares (green to red)
	this->guiData->addGuesses(this->mineProbability->getProbabilityMatrix());

	this->guiData->logSTEP3(possibleGuesses, guess, this->mineProbability->getBestProbability());

	//clear the MineProbability (for the next step)
	this->mineProbability->clearMatrix();

	substepNumber = 1;
}

void ButtonHandler::setGuiData(GuiData* guiData) {
	this->guiData = guiData;
}

ButtonHandler::ButtonHandler() {
	this->guiData = nullptr;
}

std::vector<std::vector<PaintableSquare>> ButtonHandler::getPaintableMatrix() {
	return guiData->getPaintableMatrix();
}

std::string ButtonHandler::getLastLogMessage() {
	return guiData->getLastLogMessage();
}

void ButtonHandler::setMinesweeperHandle(HWND handle) {
	minesweeperHandle = handle;
}

double ButtonHandler::getScreenScaling() {
	return screenReader->getScreenScaling();
}