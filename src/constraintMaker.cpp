#include "constraintMaker.h"

#include <algorithm>

std::vector<Constraint> ConstraintMaker::convertMinefieldToConstraints(std::vector<std::vector<Square>> minefield) {

	std::vector<Constraint> constraints;

	for (unsigned int row = 0; row < minefield.size(); row++)
	{
		for (unsigned int col = 0; col < minefield[row].size(); col++)
		{
			int currentSquare = minefield[row][col];//the square we are currently working with

			if (currentSquare < 1) { continue; } //make sure it's a numbered square
			
			int cols = minefield[0].size();
			int rows = minefield.size();

			// Define the relative positions of adjacent elements (up, down, left, right, diagonals)
			std::vector<std::pair<int, int>> directions = {
				{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
			};

			std::vector<std::pair<int, int>> variables;

			for (const auto& direction : directions) {
				int newRow = row + direction.first;
				int newCol = col + direction.second;

				// Check if the new indices are within bounds
				bool withinBounds = (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols);
				if (withinBounds) {
					bool isUnknown = minefield[newRow][newCol] == UNKNOWN;
					if (isUnknown) { variables.push_back({ newRow,newCol }); }
					bool isFlagged = minefield[newRow][newCol] == FLAGGED;
					if (isFlagged) { currentSquare -= 1; }
				}
			}

			if (currentSquare >= 1) {
				Constraint newConstraint(currentSquare, variables);
				constraints.push_back(newConstraint);
			}
			
		}
	}

	return constraints;
}

std::vector<std::pair<int, int>> ConstraintMaker::calculateMinefreeSquares(std::vector<std::vector<Square>> minefield) {

	std::vector<std::pair<int, int>> minefreeSquares;

	std::set<std::pair<int, int>> minefreeSet;

	for (unsigned int row = 0; row < minefield.size(); row++)
	{
		for (unsigned int col = 0; col < minefield[row].size(); col++)
		{
			int currentSquare = minefield[row][col];//the square we are currently working with

			if (currentSquare < 1) { continue; } //make sure it's a numbered square

			int cols = minefield[0].size();
			int rows = minefield.size();

			// Define the relative positions of adjacent elements (up, down, left, right, diagonals)
			std::vector<std::pair<int, int>> directions = {
				{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
			};

			std::vector<std::pair<int, int>> variables;

			for (const auto& direction : directions) {
				int newRow = row + direction.first;
				int newCol = col + direction.second;

				// Check if the new indices are within bounds
				bool withinBounds = (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols);
				if (withinBounds) {
					bool isUnknown = minefield[newRow][newCol] == UNKNOWN;
					if (isUnknown) { variables.push_back({ newRow,newCol }); }
					bool isFlagged = minefield[newRow][newCol] == FLAGGED;
					if (isFlagged) { currentSquare -= 1; }
				}
			}

			if (currentSquare != 0) { continue; }

			// Insert elements from the vector to the set
			for (const auto& pair : variables) {
				minefreeSet.insert(pair);
			}

		}
	}

	// Insert elements from the set to the vector
	for (const auto& pair : minefreeSet) {
		minefreeSquares.push_back(pair);
	}
	return minefreeSquares;
}

std::vector<std::pair<int, int>> ConstraintMaker::calculateMineSquares(std::vector<std::vector<Square>> minefield) {

	//there can be cases where 2 squares give the same result: that a third square is a mine
	//hence, we have to use a map to not mark and then unmark a square with a flag

	std::vector<std::pair<int, int>> mineSquares;

	std::set<std::pair<int, int>> mineSet;

	for (unsigned int row = 0; row < minefield.size(); row++)
	{
		for (unsigned int col = 0; col < minefield[row].size(); col++)
		{
			int currentSquare = minefield[row][col];//the square we are currently working with

			if (currentSquare < 1) { continue; } //make sure it's a numbered square

			int cols = minefield[0].size();
			int rows = minefield.size();

			// Define the relative positions of adjacent elements (up, down, left, right, diagonals)
			std::vector<std::pair<int, int>> directions = {
				{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
			};

			std::vector<std::pair<int, int>> variables;

			for (const auto& direction : directions) {
				int newRow = row + direction.first;
				int newCol = col + direction.second;

				// Check if the new indices are within bounds
				bool withinBounds = (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols);
				if (withinBounds) {
					bool isUnknown = minefield[newRow][newCol] == UNKNOWN;
					if (isUnknown) { variables.push_back({ newRow,newCol }); }
					bool isFlagged = minefield[newRow][newCol] == FLAGGED;
					if (isFlagged) { currentSquare -= 1; }
				}
			}

			if ( currentSquare != variables.size() ) { continue; }

			// Insert elements from the vector to the set
			for (const auto& pair : variables) {
				mineSet.insert(pair);
			}

		}
	}

	// Insert elements from the set to the vector
	for (const auto& pair : mineSet) {
		mineSquares.push_back(pair);
	}
	return mineSquares;
}

std::vector<ConstraintGroup> ConstraintMaker::groupConstraints(std::vector<Constraint> constraints) {
	std::vector<ConstraintGroup> groupedConstraints;

	for (const auto& constraint : constraints) {
		bool successfulInsertion = false;

		for (auto& group : groupedConstraints) {
			successfulInsertion = group.addConstraint(constraint);
			if (successfulInsertion) {
				break;
			}
		}

		if (!successfulInsertion) {
			ConstraintGroup newGroup;
			newGroup.addConstraint(constraint);
			groupedConstraints.push_back(newGroup);
		}
	}

	//there can be constraint groups that share a common variable
	bool canMerge = true;
	while (canMerge) {
		canMerge = false;
		for (unsigned i = 0; i < groupedConstraints.size(); ++i) {
			for (unsigned j = 0; j < groupedConstraints.size(); ++j) {

				if (i == j) {
					continue;
				}

				bool haveCommonVar = ConstraintGroup::haveCommonVariable(groupedConstraints[i], groupedConstraints[j]);

				if (haveCommonVar) {
					ConstraintGroup mergedGroup;

					//add all variables from the first group
					std::vector<Constraint> constraints1 = groupedConstraints[i].getConstraints();
					for (unsigned index = 0; index < constraints1.size(); ++index) {
						mergedGroup.addConstraint(constraints1[index]);
					}

					//add all variables from the second group
					std::vector<Constraint> constraints2 = groupedConstraints[j].getConstraints();
					for (unsigned index = 0; index < constraints2.size(); ++index) {
						mergedGroup.addConstraint(constraints2[index]);
					}

					std::swap(groupedConstraints[0],groupedConstraints[i]);
					std::swap(groupedConstraints[1],groupedConstraints[j]);
					groupedConstraints.erase(groupedConstraints.begin(),groupedConstraints.begin() + 2);
					groupedConstraints.push_back(mergedGroup);

					canMerge = true;
					break;
				}
			}

			if (canMerge) {
				break;
			}
		}
	}
	
		
	return groupedConstraints;
}

ConstraintMaker::ConstraintMaker(std::vector<std::vector<Square>> minefield) {
	this->allConstraints = convertMinefieldToConstraints(minefield);
	this->constraintGroups = groupConstraints(this->allConstraints);
	for (unsigned i = 0; i < this->constraintGroups.size(); ++i) {
		reduceConstraintGroup(constraintGroups[i]);
	}
}

std::vector<ConstraintGroup> ConstraintMaker::getConstraintGroups() {
	return this->constraintGroups;
}

std::vector<Constraint> ConstraintMaker::getAllConstraints() {
	return this->allConstraints;
}

void ConstraintMaker::reduceConstraintGroup(ConstraintGroup& group) {

	unsigned numberOfConstraints = group.constraints.size();

	for (unsigned i = 0; i < numberOfConstraints; ++i) {
		for (unsigned j = 0; j < numberOfConstraints; ++j) {
			Constraint::reduce(group.constraints[i], group.constraints[j]);
		}
	}
}