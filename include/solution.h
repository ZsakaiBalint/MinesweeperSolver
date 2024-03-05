#pragma once

#include <vector>
#include <utility>

class Solution {

private:
	std::vector<std::pair<int, int>> allVariables;
	std::vector<int> values;

public:
	Solution(std::vector<std::pair<int, int>> allVariables, std::vector<int> values);
	Solution(std::vector<std::pair<int, int>> allVariables);
	Solution();
	Solution(Solution& other);
	void addValue(int newValue);
	std::vector<std::pair<int, int>> getAllVariables();
	std::vector<int> getValues();
};