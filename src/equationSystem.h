#pragma once

#include "equation.h"

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

class EquationSystem {
    public:
        EquationSystem();
        void add(Equation e);
        void solve();
    private:
        std::vector<Equation> equations;
        std::set<std::pair<int, int>> allVariables;

        std::vector<std::vector<int>> allSolutions;

        int countVarOccurence(const std::pair<int, int>& variable);
        void recursiveSolve();
};