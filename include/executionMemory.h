#pragma once
#include <vector>
#include "difficulty.h"

class ExecutionMemory {
private:
	std::vector<std::vector<bool>> memoryMatrix;
public:
	void MarkAsExecuted(std::pair<int, int> square);
	bool isExecuted(std::pair<int, int> square);
	ExecutionMemory(Difficulty difficulty);
};