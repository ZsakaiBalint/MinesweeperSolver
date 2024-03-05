#pragma once

#include "set"
#include "constraint.h"
#include "solution.h"

class ConstraintGroup {
private:
	std::vector<Constraint> constraints;
	std::set<std::pair<int, int>> allVariables;
public:
	bool isValidAssignment(Solution solution);
	bool isCompleteAssignment(Solution solution);
	ConstraintGroup();
	ConstraintGroup(const ConstraintGroup& other);
	bool addConstraint(Constraint newConstraint);
	bool operator==(const ConstraintGroup& other) const;
	std::vector<Constraint> getConstraints();
	std::vector<std::pair<int, int>> getAllVariables();
	static bool haveCommonVariable(ConstraintGroup c1, ConstraintGroup c2);
	friend std::ostream& operator<<(std::ostream& os, const ConstraintGroup& obj);

	friend class ConstraintMaker; //only ConstraintMaker::reduceConstraintGroup should be friend!!! HOW TO ACHIEVE THIS???

	std::string toString();
};