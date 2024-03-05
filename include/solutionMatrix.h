#pragma once
#include <vector>
#include <algorithm>
#include <unordered_set>

class SolutionMatrix {

private:
    std::vector<std::pair<int, int>> allVariables;
    std::vector<std::vector<int>> allValues;
public:
    SolutionMatrix(std::vector<std::pair<int, int>> allVariables, std::vector<std::vector<int>> allValues);
    std::vector<std::vector<int>> getAllValues() const;
    std::vector<std::pair<int, int>> getAllVariables() const;
    void sortSolutionMatrix(SolutionMatrix& sm);
    bool operator==(const SolutionMatrix& other);
};