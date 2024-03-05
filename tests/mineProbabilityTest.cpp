#include "pch.h"
#include "../src/mineProbability.cpp"

TEST(MineProbability, addSolutionMatrix) {
	//adding one solution matrix
	Beginner beginner;
	MinefieldMemory* memory = new MinefieldMemory(beginner);
	MineProbability mineProbability(beginner,memory);

	std::vector<std::pair<int, int>> allVariables = { {1,1},{1,4},{3,6},{2,6},{2,0},{1,3},{1,6},{1,0},{1,2},{1,5} };
	std::vector<std::vector<int>> allValues = {
		{0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 1, 1, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	};
	SolutionMatrix sm(allVariables, allValues);

	mineProbability.addSolutionMatrix(sm);
	std::vector<std::vector<double>> probabilityMatrix = mineProbability.getProbabilityMatrix();

	std::vector<std::vector<double>> probabilityMatrixTest = {
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{0.25,	  0.25,	  0.25,	   0.5,	  0.25,   0.25,    0.5,     -2},
		{0.25,	    -2,		-2,		-2,		-2,		-2,    0.5,		-2},
		{-2,		-2,		-2,		-2,		-2,		-2,	   0.5,		-2},
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,		-2}
	};
	
	EXPECT_EQ(probabilityMatrix, probabilityMatrixTest);
	delete memory;

	//adding multiple solution matrices
	MinefieldMemory* memory1 = new MinefieldMemory(beginner);
	MineProbability mineProbability1(beginner,memory1);

	std::vector<std::pair<int, int>> allVariables1 = { {1,1},{1,4},{3,6},{2,6},{2,0},{1,3},{1,6},{1,0},{1,2},{1,5} };
	std::vector<std::vector<int>> allValues1 = {
		{0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 1, 1, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	};
	SolutionMatrix sm1(allVariables1, allValues1);
	mineProbability1.addSolutionMatrix(sm1);

	std::vector<std::pair<int, int>> allVariables2 = { {5,2} };
	std::vector<std::vector<int>> allValues2 = {
		{1}
	};
	SolutionMatrix sm2(allVariables2, allValues2);
	mineProbability1.addSolutionMatrix(sm2);

	std::vector<std::pair<int, int>> allVariables3 = { {4,7},{5,7},{6,7},{7,7} };
	std::vector<std::vector<int>> allValues3 = {
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 1 },
	};
	SolutionMatrix sm3(allVariables3, allValues3);
	mineProbability1.addSolutionMatrix(sm3);

	std::vector<std::vector<double>> probabilityMatrix1 = mineProbability1.getProbabilityMatrix();

	std::vector<std::vector<double>> probabilityMatrixTest1 = {
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{0.25,	  0.25,	  0.25,	   0.5,	  0.25,   0.25,    0.5,     -2},
		{0.25,	    -2,		-2,		-2,		-2,		-2,    0.5,		-2},
		{-2,		-2,		-2,		-2,		-2,		-2,	   0.5,	    -2},
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,	   0.5},
		{-2,		-2,		 1,		-2,		-2,		-2,		-2,		 1},
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,	   0.5},
		{-2,		-2,		-2,		-2,		-2,		-2,		-2,	   0.5}
	};

	EXPECT_EQ(probabilityMatrix1, probabilityMatrixTest1);
	delete memory1;
}

TEST(MineProbability, clearMatrix) {

	Beginner beginner;
	MinefieldMemory* memory = new MinefieldMemory(beginner);
	MineProbability mineProbability(beginner,memory);

	std::vector<std::pair<int, int>> allVariables1 = { {1,1},{1,4},{3,6},{2,6},{2,0},{1,3},{1,6},{1,0},{1,2},{1,5} };
	std::vector<std::vector<int>> allValues1 = {
		{0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 1, 1, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	};

	SolutionMatrix sm1(allVariables1, allValues1);
	mineProbability.addSolutionMatrix(sm1);

	std::vector<std::pair<int, int>> allVariables2 = { {5,2} };
	std::vector<std::vector<int>> allValues2 = {
		{1}
	};
	SolutionMatrix sm2(allVariables2, allValues2);
	mineProbability.addSolutionMatrix(sm2);

	std::vector<std::pair<int, int>> allVariables3 = { {4,7},{5,7},{6,7},{7,7} };
	std::vector<std::vector<int>> allValues3 = {
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 1 },
	};
	SolutionMatrix sm3(allVariables3, allValues3);
	mineProbability.addSolutionMatrix(sm3);

	mineProbability.clearMatrix();

	std::vector<std::vector<double>> probabilityMatrix1 = mineProbability.getProbabilityMatrix();

	std::vector<std::vector<double>> probabilityMatrixTest1 = {
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
	};

	EXPECT_EQ(probabilityMatrix1, probabilityMatrixTest1);
	delete memory;
}

TEST(MineProbability,addKnownSquares) {
	Beginner beginner;
	MinefieldMemory* memory = new MinefieldMemory(beginner);
	MineProbability mineProbability(beginner, memory);

	memory->markAsMine({ {2,2} });
	memory->markAsMinefree({ {3,3} });
	memory->markAsMine({ {4,4} });
	memory->markAsMinefree({ {5,5} });

	mineProbability.addKnownSquares();

	std::vector<std::vector<double>> probabilityMatrix = mineProbability.getProbabilityMatrix();

	std::vector<std::vector<double>> probabilityMatrixTest = {
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-1,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-1,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-1,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-1,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
		{-2,	-2,		-2,		-2,		-2,		-2,		-2,		-2},
	};

	EXPECT_EQ(probabilityMatrix, probabilityMatrixTest);

	delete memory;
}

TEST(MineProbability, calculateUnknownSquares) {
	Beginner beginner;
	MinefieldMemory* memory = new MinefieldMemory(beginner);
	MineProbability mineProbability(beginner, memory);

	memory->markAsMine({ {2,2} });
	memory->markAsMinefree({ {3,3} });
	memory->markAsMine({ {4,4} });
	memory->markAsMinefree({ {5,5} });

	std::vector<std::pair<int, int>> allVariables1 = { {1,1},{1,4},{3,6},{2,6},{2,0},{1,3},{1,6},{1,0},{1,2},{1,5} };
	std::vector<std::vector<int>> allValues1 = {
		{0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
		{0, 0, 0, 1, 0, 1, 1, 1, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	};
	SolutionMatrix sm1(allVariables1, allValues1);
	mineProbability.addSolutionMatrix(sm1);

	std::vector<std::pair<int, int>> allVariables2 = { {5,2} };
	std::vector<std::vector<int>> allValues2 = {
		{1}
	};
	SolutionMatrix sm2(allVariables2, allValues2);
	mineProbability.addSolutionMatrix(sm2);

	std::vector<std::pair<int, int>> allVariables3 = { {4,7},{5,7},{6,7},{7,7} };
	std::vector<std::vector<int>> allValues3 = {
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 1 },
	};
	SolutionMatrix sm3(allVariables3, allValues3);
	mineProbability.addSolutionMatrix(sm3);

	mineProbability.addKnownSquares();
	mineProbability.calculateUnknownSquares();

	std::vector<std::vector<double>> probabilityMatrix = mineProbability.getProbabilityMatrix();

	std::vector<std::vector<double>> probabilityMatrixTest = {
		{ 0.067, 0.067, 0.067, 0.067, 0.067, 0.067, 0.067, 0.067 },
		{ 0.25,  0.25,  0.25,  0.5,   0.25,  0.25,  0.5,   0.067 },
		{ 0.25,  0.067, -1,    0.067, 0.067, 0.067, 0.5,   0.067 },
		{ 0.067, 0.067, 0.067, -1,    0.067, 0.067, 0.5,   0.067 },
		{ 0.067, 0.067, 0.067, 0.067, -1,    0.067, 0.067, 0.5   },
		{ 0.067, 0.067, 1,     0.067, 0.067, -1,    0.067, 1     },
		{ 0.067, 0.067, 0.067, 0.067, 0.067, 0.067, 0.067, 0.5   },
		{ 0.067, 0.067, 0.067, 0.067, 0.067, 0.067, 0.067, 0.5   }
	};

	EXPECT_EQ(probabilityMatrix, probabilityMatrixTest);
	delete memory;


	//the function works if we didn't provide any solution matrices
	Intermediate intermediate;
	MinefieldMemory* memory1 = new MinefieldMemory(intermediate);
	MineProbability mineProbability1(intermediate, memory1);

	mineProbability1.calculateUnknownSquares();

	std::vector<std::vector<double>> probabilityMatrix1 = mineProbability1.getProbabilityMatrix();

	std::vector<std::vector<double>> probabilityMatrixTest1 = {
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 },
		{ 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156, 0.156 }
	};

	EXPECT_EQ(probabilityMatrix1, probabilityMatrixTest1);
	delete memory1;
}

TEST(MineProbability, getBestGuesses) {

	Beginner beginner;
	MinefieldMemory* memory = new MinefieldMemory(beginner);
	MineProbability mineProbability(beginner, memory);

	std::vector<std::pair<int, int>> bestGuesses = mineProbability.getBestGuesses();
	std::vector<std::pair<int, int>> bestGuessesTest = { {0,0}, {0,7}, {7,0}, {7,7} };

	EXPECT_EQ(bestGuesses, bestGuessesTest);
	delete memory;
};

TEST(MineProbability, equality) {

	Beginner beginner;
	MinefieldMemory* memory = new MinefieldMemory(beginner);
	MineProbability mineProbability(beginner, memory);

	std::pair<double, SquareLocation> pair1 = { -2,INTERNAL };
	std::pair<double, SquareLocation> pair2 = { -2,EDGE };
	std::pair<double, SquareLocation> pair3 = { -2,EDGE };

	EXPECT_FALSE(pair1 == pair2);
	EXPECT_TRUE(pair2 == pair3);

	delete memory;
}

TEST(MineProbability, smallerThan) {

	Beginner beginner;
	MinefieldMemory* memory = new MinefieldMemory(beginner);
	MineProbability mineProbability(beginner, memory);

	std::pair<double, SquareLocation> pair1 = { -2, CORNER };
	std::pair<double, SquareLocation> pair2 = { 0.562, EDGE };
	std::pair<double, SquareLocation> pair3 = { 1, INTERNAL };
	std::pair<double, SquareLocation> pair4 = { 0.567, INTERNAL };

	EXPECT_TRUE(pair1 < pair2);
	EXPECT_TRUE(pair2 < pair3);
	EXPECT_TRUE(pair2 < pair4);

	delete memory;
}