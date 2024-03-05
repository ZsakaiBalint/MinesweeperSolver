#include "pch.h"
#include "../src/solutionMatrix.cpp"

TEST(SolutionMatrix, equality) {

	//the two matrices are equal, with different column sequence
	std::vector<std::pair<int, int>> allVariables1 = { {1,4},{2,0},{2,6},{1,1},{1,3},{3,6},{1,0},{1,6},{1,2},{1,5} };
	std::vector<std::vector<int>> allValues1 {
		{ 0,1,0,0,1,1,0,1,0,0 },
		{ 0,1,1,0,1,0,0,1,0,0 },
		{ 0,0,0,0,0,1,0,0,1,1 },
		{ 0,0,1,0,0,0,0,0,1,1 },
		{ 1,0,0,1,0,1,0,0,0,0 },
		{ 1,0,1,1,0,0,0,0,0,0 },
		{ 0,0,0,0,1,1,1,1,0,0 },
		{ 0,0,1,0,1,0,1,1,0,0 }
	};

	std::vector<std::pair<int, int>> allVariables2 = { {1,5},{1,6},{1,2},{1,4},{2,0},{1,1},{3,6},{1,0},{1,3},{2,6} };
	std::vector<std::vector<int>> allValues2 {
		{ 0,1,0,0,1,0,1,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,1 },
		{ 1,0,1,0,0,0,1,0,0,0 },
		{ 1,0,1,0,0,0,0,0,0,1 },
		{ 0,0,0,1,0,1,1,0,0,0 },
		{ 0,0,0,1,0,1,0,0,0,1 },
		{ 0,1,0,0,0,0,1,1,1,0 },
		{ 0,1,0,0,0,0,0,1,1,1 }
	};

	SolutionMatrix sm1(allVariables1, allValues1);
	SolutionMatrix sm2(allVariables2, allValues2);
	EXPECT_TRUE(sm1 == sm2);
	
	//the two matrices are different
	std::vector<std::pair<int, int>> allVariables3 = { {123,456},{2,0},{66,42},{14,18},{1,3},{3,6},{100,101},{1,6},{1,2},{1,5} };
	std::vector<std::vector<int>> allValues3 {
		{ 0,1,0,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,0 }
	};

	std::vector<std::pair<int, int>> allVariables4 = { {1,5},{1,6},{1,2},{1,4},{2,0},{1,1},{3,6},{1,0},{1,3},{2,6} };
	std::vector<std::vector<int>> allValues4 {
		{ 0,1,0,0,1,0,1,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,1 },
		{ 1,0,1,0,0,0,1,0,0,0 },
		{ 1,0,1,0,0,0,0,0,0,1 },
		{ 0,0,0,1,0,1,1,0,0,0 },
		{ 0,0,0,1,0,1,0,0,0,1 },
		{ 0,1,0,0,0,0,1,1,1,0 },
		{ 0,1,0,0,0,0,0,1,1,1 }
	};

	SolutionMatrix sm3(allVariables3, allValues3);
	SolutionMatrix sm4(allVariables4, allValues4);
	EXPECT_FALSE(sm3 == sm4);

	//the two matrices are equal, with different column and row sequence
	std::vector<std::pair<int, int>> allVariables5 = { {1,4},{2,0},{2,6},{1,1},{1,3},{3,6},{1,0},{1,6},{1,2},{1,5} };
	std::vector<std::vector<int>> allValues5 {
		
		{ 0,1,1,0,1,0,0,1,0,0 },
		{ 0,1,0,0,1,1,0,1,0,0 },
		{ 0,0,1,0,0,0,0,0,1,1 },
		{ 0,0,0,0,0,1,0,0,1,1 },
		{ 1,0,0,1,0,1,0,0,0,0 },
		{ 0,0,1,0,1,0,1,1,0,0 },
		{ 0,0,0,0,1,1,1,1,0,0 },
		{ 1,0,1,1,0,0,0,0,0,0 }
	};

	std::vector<std::pair<int, int>> allVariables6 = { {1,5},{1,6},{1,2},{1,4},{2,0},{1,1},{3,6},{1,0},{1,3},{2,6} };
	std::vector<std::vector<int>> allValues6 {
		{ 0,1,0,0,1,0,1,0,1,0 },
		{ 0,1,0,0,1,0,0,0,1,1 },
		{ 1,0,1,0,0,0,1,0,0,0 },
		{ 1,0,1,0,0,0,0,0,0,1 },
		{ 0,0,0,1,0,1,1,0,0,0 },
		{ 0,0,0,1,0,1,0,0,0,1 },
		{ 0,1,0,0,0,0,1,1,1,0 },
		{ 0,1,0,0,0,0,0,1,1,1 }
	};

	SolutionMatrix sm5(allVariables5, allValues5);
	SolutionMatrix sm6(allVariables6, allValues6);
	EXPECT_TRUE(sm5 == sm6);
}