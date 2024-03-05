#include "Constraint.h"

//   you can create a constraint by providing all variables at once
Constraint::Constraint(int sum, std::vector<std::pair<int, int>> variables) {
    this->sum = sum;
    this->variables = variables;
}

//   or you can create a constraint by providing variables one at a time
Constraint::Constraint(int sum) {
    this->sum = sum;
}

void Constraint::addVar(std::pair<int, int> newVar) {
    variables.push_back(newVar);
}

std::vector<std::pair<int, int>> Constraint::getVariables() const {
    return this->variables;
}

//check if the constraint contains a given variable
bool Constraint::containsVar(std::pair<int, int> givenVar) {
    for (const auto& variable : variables) {
        if (variable == givenVar) {
            return true;
        }
    }
    return false;
}

// the given solution contain all variables that
//the constraint has (with extra variables allowed)
//and for all of them, a corresponding value exists
bool Constraint::isCompleteAssignment(Solution solution) {
    //iterate through all variables in the constraint
    for (const auto& variable : variables) {
        bool found = false;
        for (long unsigned int index = 0; index < solution.getAllVariables().size(); ++index) {
            //the current variable exists 
            //and a corresponding value also exists
            if (variable == solution.getAllVariables()[index] && index < solution.getValues().size()) {
                found = true;
                continue;
            }
        }
        if (!found) { return false; }
    }
    return true;
}

//check if the given solution satisfies the constraint
//there can be variables that are not part of the constraint
//there can be more variables than values (no value assigned yet)
bool Constraint::isValidAssignment(Solution solution) {

    int sumOfGivenValues = 0;

    bool contains = isCompleteAssignment(solution);

    //all values are assigned
    if (contains) {
        for (long unsigned int index = 0; index < solution.getAllVariables().size(); ++index) {
            if (containsVar(solution.getAllVariables()[index])) {
                sumOfGivenValues += solution.getValues()[index];
            }
        }
        return sumOfGivenValues == sum;
    }

    //not all values are assigned
    else {
        int numberOfUnassignedValues = 0;

        bool condition1 = false;
        bool condition2 = false;

        for (long unsigned int index = 0; index < solution.getAllVariables().size(); ++index) {
            if (containsVar(solution.getAllVariables()[index]) && index < solution.getValues().size()) {
                sumOfGivenValues += solution.getValues()[index];
            }
            else if (containsVar(solution.getAllVariables()[index]) && !(index < solution.getValues().size())) {
                numberOfUnassignedValues++;
            }
        }

        condition1 = sumOfGivenValues <= sum;
        condition2 = (numberOfUnassignedValues >= (sum - sumOfGivenValues));

        return condition1 && condition2;
    }

}

bool Constraint::operator== (const Constraint& other) const  {
    if (sum != other.sum)
        return false;

    if (variables.size() != other.variables.size())
        return false;

    // Create copies of the variables arrays to sort them
    std::vector<std::pair<int,int>> sortedVariables = this->getVariables();
    std::vector<std::pair<int, int>> sortedOtherVariables = other.getVariables();

    // Sort the arrays
    std::sort(sortedVariables.begin(), sortedVariables.end());
    std::sort(sortedOtherVariables.begin(), sortedOtherVariables.end());

    // Compare the sorted arrays
    for (size_t i = 0; i < sortedVariables.size(); ++i) {
        if (sortedVariables[i] != sortedOtherVariables[i])
            return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Constraint& obj) {
    os << "Sum: " << obj.sum << ", Variables: [";
    for (size_t i = 0; i < obj.variables.size(); ++i) {
        os << "(" << obj.variables[i].first << ", " << obj.variables[i].second << ")";
        if (i != obj.variables.size() - 1)
            os << ", ";
    }
    os << "]";
    return os;
}

bool Constraint::isSubsetOf(Constraint first, Constraint second) {

    if (first == second) {
        return false;
    }

    std::vector<std::pair<int, int>> variables1 = first.getVariables();
    std::vector<std::pair<int, int>> variables2 = second.getVariables();

    for (const auto& elem : variables1) {
        if (std::find(variables2.begin(), variables2.end(), elem) == variables2.end()) {
            return false;
        }
    }
    return true;
}

Constraint::Constraint(const Constraint& c) {
    this->sum = c.sum;
    this->variables = c.variables;
}

Constraint::Constraint() {
    this->sum = 0;
    this->variables = std::vector<std::pair<int, int>>();
}

void Constraint::reduce(Constraint& first, Constraint& second) {

    Constraint subset;
    Constraint superset;
    bool firstArgumentIsSubset;

    //determine which Constraint is the subset and which is the superset
    if (isSubsetOf(first, second)) {
        firstArgumentIsSubset = true;
        subset = Constraint(first);
        superset = Constraint(second);
    }
    else if (isSubsetOf(second, first)) {
        firstArgumentIsSubset = false;
        subset = Constraint(second);
        superset = Constraint(first);
    }
    else {
        return;
    }

    //reduce the superset with the subset
    superset.sum -= subset.sum;

    // Remove common pairs from superset's variables
    std::vector<std::pair<int, int>> subsetVars = subset.getVariables();
    std::vector<std::pair<int, int>> supersetVars = superset.getVariables();
    for (unsigned i = 0; i < supersetVars.size(); ++i) {
        auto variable = std::find(subsetVars.begin(), subsetVars.end(), supersetVars[i]);
        if (variable != subsetVars.end()) {
            // The pair is present in subsetVars, so remove it from supersetVars
            supersetVars.erase(supersetVars.begin() + i);
            --i; // Decrement 'i' to account for the erased element
        }
    }
    superset.variables = supersetVars;

    //modify the superset Constraint with it's reduced version
    if (firstArgumentIsSubset) {
        second = superset;
    }
    else {
        first = superset;
    }
}

std::string Constraint::toString() {
    std::string constraintAsString = "";

    constraintAsString += "Sum: " + std::to_string(sum) + ", Variables: [";
    for (size_t i = 0; i < variables.size(); ++i) {
        std::string first = std::to_string(variables[i].first);
        std::string second = std::to_string(variables[i].second);
        constraintAsString += "(" + first + ", " + second + ")";
        if (i != variables.size() - 1)
            constraintAsString += ", ";
    }
    constraintAsString += "]";
    
    return constraintAsString;
}