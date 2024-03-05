#pragma once
#include "constraint.h"
#include "constraintGroup.h"
#include "solution.h"
#include "solutionMatrix.h"
#include <vector>
#include <set>

class ConstraintGroupSolver {

private:
    std::vector<std::pair<int, int>> allVariables;
    std::vector<std::vector<int>> allValues;
    ConstraintGroup constraintGroup;

public:
    ConstraintGroupSolver(ConstraintGroup constraintGroup);
    void solve(std::vector<int> currentValues = std::vector<int>());
    SolutionMatrix getSolutionMatrix();
};