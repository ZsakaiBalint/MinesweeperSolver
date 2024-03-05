#include "constraintGroup.h"

bool ConstraintGroup::isValidAssignment(Solution solution) {
	bool allValid = true;
	for (unsigned i = 0; i < constraints.size(); ++i) {
		allValid &= constraints[i].isValidAssignment(solution);
		if (!allValid) { return false; }
	}
	return true;
}

bool ConstraintGroup::isCompleteAssignment(Solution solution) {
	bool allComplete = true;
	for (unsigned i = 0; i < constraints.size(); ++i) {
		allComplete &= constraints[i].isCompleteAssignment(solution);
		if (!allComplete) { return false; }
	}
	return true;
}

ConstraintGroup::ConstraintGroup() {
	this->constraints = std::vector<Constraint>();
	this->allVariables = std::set<std::pair<int, int>>();
}

ConstraintGroup::ConstraintGroup(const ConstraintGroup& other) {
	this->constraints = other.constraints;
	this->allVariables = other.allVariables;
}

//we can insert a new constraint to the constraint group only
//if the constraint and the group have at least one common variable
bool ConstraintGroup::addConstraint(Constraint newConstraint) {
	bool successfulInsertion = false;
	std::vector<std::pair<int, int>> newVariables = newConstraint.getVariables();

	for(unsigned i = 0;i<newVariables.size();++i) {
		for (const auto& pair : allVariables) {
			if (pair == newVariables[i]) {
				successfulInsertion = true;
				break;
			}
		}
	}

	if (constraints.size() == 0) {
		successfulInsertion = true;
	}

	if (successfulInsertion) {
		constraints.push_back(newConstraint);
		for (int i = 0; i < newVariables.size(); ++i) {
			allVariables.insert(newVariables[i]);
		}
	}

	return successfulInsertion;
}

bool ConstraintGroup::operator==(const ConstraintGroup& other) const {
	if (constraints.size() != other.constraints.size())
		return false;

	if (allVariables.size() != other.allVariables.size())
		return false;

	// Create copies of the variables arrays to sort them
	std::vector<Constraint> constraints = this->constraints;
	std::vector<Constraint> otherConstraints = other.constraints;

	// Compare the sorted arrays
	for (unsigned i = 0; i < constraints.size(); ++i) {
		bool foundConstraint = false;
		for (unsigned j = 0; j < otherConstraints.size(); ++j) {
			if (constraints[i] == otherConstraints[j]) {
				foundConstraint = true;
				continue;
			}
		}
		if (!foundConstraint) {
			return false;
		}
	}

	return true;
}

std::vector<Constraint> ConstraintGroup::getConstraints() {
	return this->constraints;
}

std::vector<std::pair<int, int>> ConstraintGroup::getAllVariables() {
	std::set<std::pair<int, int>> allVarsSet = this->allVariables;
	std::vector<std::pair<int, int>> allVars(allVarsSet.begin(), allVarsSet.end());
	return allVars;
}

std::ostream& operator<<(std::ostream& os, const ConstraintGroup& obj) {
	os << "{";
	for(unsigned i = 0; i < obj.constraints.size(); ++i) {
		os << obj.constraints[i];
		if (i != obj.constraints.size() - 1)
			os << ", ";
	}
	os << "}";
	return os;
}

bool ConstraintGroup::haveCommonVariable(ConstraintGroup c1, ConstraintGroup c2) {
	//std::set<std::pair<int, int>> variables1 = c1.allVariables;
	//std::set<std::pair<int, int>> variables2 = c2.allVariables;
	//DEBUG
	std::vector<std::pair<int, int>> allVars1 = c1.getAllVariables();
	std::vector<std::pair<int, int>> allVars2 = c2.getAllVariables();
	//convert vector to set
	std::set<std::pair<int, int>> variables1(allVars1.begin(), allVars1.end());
	std::set<std::pair<int, int>> variables2(allVars2.begin(), allVars2.end());

	for (const auto& variable : variables1) {
		if (variables2.find(variable) != variables2.end()) {
			//found a common variable
			return true;
		}
	}

	//no common variable found
	return false;
}

std::string ConstraintGroup::toString() {
	std::string constraintGroupAsString = "";
	constraintGroupAsString += "{";
	for (unsigned i = 0; i < constraints.size(); ++i) {
		constraintGroupAsString += constraints[i].toString();
		if (i != constraints.size() - 1)
			constraintGroupAsString += ", ";
	}
	constraintGroupAsString += "}; ";
	return constraintGroupAsString;
}