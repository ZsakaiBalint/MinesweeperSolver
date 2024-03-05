#include "solutionMatrix.h"

SolutionMatrix::SolutionMatrix(std::vector<std::pair<int, int>> allVariables, std::vector<std::vector<int>> allValues) {
	this->allVariables = allVariables;
	this->allValues = allValues;
}

std::vector<std::vector<int>> SolutionMatrix::getAllValues() const {
	return allValues;
}

std::vector<std::pair<int, int>> SolutionMatrix::getAllVariables() const {
	return allVariables;
}

bool SolutionMatrix::operator== (const SolutionMatrix& other) {
    SolutionMatrix matrix1(this->allVariables, this->allValues);
    SolutionMatrix matrix2(other.allVariables, other.allValues);

    sortSolutionMatrix(matrix1);
    sortSolutionMatrix(matrix2);

    //check if variables are equal
    if (matrix1.allVariables.size() != matrix2.allVariables.size()) {
        return false;
    }
    for (unsigned i = 0; i < matrix1.allVariables.size(); ++i) {
        if (matrix1.allVariables[i] != matrix2.allVariables[i]) {
            return false;
        }
    }

    //check if the matrices are equal
    if (matrix1.allValues.size() != matrix2.allValues.size()) {
        return false;
    }
    /*
    for (unsigned i = 0; i < matrix1.allValues.size(); ++i) {
        if (matrix1.allValues[i].size() != matrix2.allValues[i].size()) {
            return false;
        }
        for (unsigned j = 0; j < matrix1.allValues[i].size(); ++j) {
            if (matrix1.allValues[i][j] != matrix2.allValues[i][j]) {
                return false;
            }
        }
    }
    */

    for (unsigned i = 0; i < matrix1.allValues.size(); ++i) {
        bool found = false;
        for (unsigned j = 0; j < matrix2.allValues.size(); ++j) {
            if (matrix1.allValues[i] == matrix2.allValues[j]) { found = true; continue; }
        }
        if (!found) { return false; }
    }
    return true;

    //return true;
}

void SolutionMatrix::sortSolutionMatrix(SolutionMatrix& sm) {

    std::vector<std::pair<int, int>> variables = sm.allVariables;
    std::vector<std::vector<int>> matrix = sm.allValues;

    //1) note each variable's index before the sorting
    std::vector<std::pair<int, std::pair<int, int>>> variablesWithIndexes;
    for (unsigned i = 0; i < variables.size(); ++i) {
        variablesWithIndexes.push_back({ i, variables[i] });
    }

    //2) sort the new vector based on the pairs
    sort(variablesWithIndexes.begin(), variablesWithIndexes.end(), [](const auto& a, const auto& b) {
        if (a.second.first != b.second.first) {
            return a.second.first < b.second.first;
        }
        else {
            return a.second.second < b.second.second;
        }
    });

    //3) arrange the matrix's columns based on the indexes from point '1)'
    std::vector<std::vector<int>> sortedMatrix;
    // populate the matrix with zeros
    for (unsigned i = 0; i < matrix.size(); ++i) {
        std::vector<int> newRowWithZeros;
        for (unsigned j = 0; j < matrix[0].size(); ++j) {
            newRowWithZeros.push_back(0);
        }
        sortedMatrix.push_back(newRowWithZeros);
    }
    // modify the columns
    for (unsigned i = 0; i < matrix.size(); ++i) {
        for (unsigned j = 0; j < matrix[0].size(); ++j) {
            int previusColumnIndex = variablesWithIndexes[j].first;
            sortedMatrix[i][j] = matrix[i][previusColumnIndex];
        }
    }

    variables.clear();
    for (unsigned i = 0; i < variablesWithIndexes.size(); ++i) {
        variables.push_back(variablesWithIndexes[i].second);
    }
    sm.allVariables = variables;
    sm.allValues = sortedMatrix;
}