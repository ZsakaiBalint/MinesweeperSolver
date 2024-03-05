#pragma once
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <string>

#include "solution.h"

class Constraint {
private:
	int sum;
	std::vector<std::pair<int,int>> variables;

public:
	bool isCompleteAssignment(Solution solution);
	bool isValidAssignment(Solution solution);
	bool containsVar(std::pair<int, int> givenVar);

	Constraint();
    Constraint(int sum, std::vector<std::pair<int, int>> variables);
    Constraint(int sum);
	Constraint(const Constraint& c);

    void addVar(std::pair<int, int> newVar);

	std::vector<std::pair<int, int>> getVariables() const;

	bool operator==(const Constraint& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Constraint& obj);

	static bool isSubsetOf(Constraint first, Constraint second);

	static void reduce(Constraint& first, Constraint& second);

	std::string toString();
};