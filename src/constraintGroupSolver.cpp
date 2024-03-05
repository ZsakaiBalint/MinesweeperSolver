#include "constraintGroupSolver.h"

ConstraintGroupSolver::ConstraintGroupSolver(ConstraintGroup constraintGroup) : constraintGroup(constraintGroup) {
    this->allVariables = constraintGroup.getAllVariables();
    this->allValues = std::vector<std::vector<int>>();
}

void ConstraintGroupSolver::solve(std::vector<int> currentValues) {

    //check if the given values satisfy all constraints
    Solution newSolution(allVariables, currentValues);
    bool isValidAssignment = constraintGroup.isValidAssignment(newSolution);

    if (isValidAssignment) {

        bool isCompleteAssignment = constraintGroup.isCompleteAssignment(newSolution);

        if (isCompleteAssignment) {
            //we found a solution
            allValues.push_back(currentValues);
        }
        else {
            //we didn't find a solution 
            //recursively check adding 0 and or adding 1 to the
            //solution satisfies the constraints
            std::vector<int> currentValuesWithZero = currentValues;
            currentValuesWithZero.push_back(0);
            solve(currentValuesWithZero);

            std::vector<int> currentValuesWithOne = currentValues;
            currentValuesWithOne.push_back(1);
            solve(currentValuesWithOne);
        }
    }
}

SolutionMatrix ConstraintGroupSolver::getSolutionMatrix() {
    return SolutionMatrix(this->allVariables, this->allValues);
}