#include "solution.h"

Solution::Solution(std::vector<std::pair<int, int>> allVariables, std::vector<int> values) {
	this->allVariables = allVariables;
	this->values = values;
}

Solution::Solution(std::vector<std::pair<int, int>> allVariables) {
	this->allVariables = allVariables;
	this->values = std::vector<int>();
}

Solution::Solution() {
	this->allVariables = std::vector<std::pair<int, int>>();
	this->values = std::vector<int>();
}

Solution::Solution(Solution& other) {
	this->allVariables = other.allVariables;
	this->values = other.values;
}

void Solution::addValue(int newValue) {
	values.push_back(newValue);
}

std::vector<std::pair<int, int>> Solution::getAllVariables() {
	return this->allVariables;
}


std::vector<int> Solution::getValues() {
	return this->values;
}