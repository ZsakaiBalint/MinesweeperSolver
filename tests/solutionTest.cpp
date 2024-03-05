#include "pch.h"
#include "../src/solution.cpp"

TEST(Solution, addValue) {
	Solution s( { {0,2},{1,2},{2,2},{3,0},{3,1},{3,2} },{0, 1, 0, 0, 0} );
	s.addValue(1);

	std::vector<std::pair<int, int>> allVariables = s.getAllVariables();
	std::vector<std::pair<int, int>> allVariablesTest = { {0,2},{1,2},{2,2},{3,0},{3,1},{3,2} };
	std::vector<int> allValues = s.getValues();
	std::vector<int> allValuesTest = { 0, 1, 0, 0, 0, 1 };

	EXPECT_EQ(allVariables,allVariablesTest);
	EXPECT_EQ(allValues,allValuesTest);
}