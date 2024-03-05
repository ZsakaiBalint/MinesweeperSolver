#pragma once
#include <vector>
#include "screenReader.h"
#include "constraint.h"
#include "constraintGroup.h"

class ConstraintMaker {
private:
	std::vector<Constraint> allConstraints;
	std::vector<ConstraintGroup> constraintGroups;

public:
	std::vector<std::pair<int, int>> calculateMinefreeSquares(std::vector<std::vector<Square>> minefield);
	std::vector<std::pair<int, int>> calculateMineSquares(std::vector<std::vector<Square>> minefield);
	std::vector<Constraint> convertMinefieldToConstraints(std::vector<std::vector<Square>> minefield);
	std::vector<ConstraintGroup> groupConstraints(std::vector<Constraint> constraints);
	ConstraintMaker(std::vector<std::vector<Square>> minefield);
	std::vector<ConstraintGroup> getConstraintGroups();
	std::vector<Constraint> getAllConstraints();

	static void reduceConstraintGroup(ConstraintGroup& group);
};