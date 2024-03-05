#include "pch.h"
#include "../src/constraintGroup.cpp"

TEST(ConstraintGroup, equality) {

	//the two constraint groups contain the same constraints
	Constraint c1(1, { {0,2},{1,2} });
	Constraint c2(1, { {0,2},{1,2},{2,2} });
	Constraint c3(2, { {3,0},{3,1},{3,2},{2,2},{1,2} });
	ConstraintGroup cg1;
	ConstraintGroup cg2;

	cg1.addConstraint(c1);
	cg1.addConstraint(c2);
	cg1.addConstraint(c3);
	
	cg2.addConstraint(c2);
	cg2.addConstraint(c3);
	cg2.addConstraint(c1);

	EXPECT_TRUE(cg1 == cg2);

	//the two constraint groups contain different constraints
	Constraint c4(1, { {66,66},{77,77} });
	Constraint c5(1, { {77,77},{1,2},{88,88} });
	Constraint c6(2, { {3,0},{77,77},{3,2},{99,99},{1,2} });
	ConstraintGroup cg3;

	cg3.addConstraint(c4);
	cg3.addConstraint(c5);
	cg3.addConstraint(c6);

	EXPECT_FALSE(cg1 == cg3);
}

TEST(ConstraintGroup, addConstraint) {
	//adding a constraint to an empty constraint group
	Constraint c1(1, { {0,2},{1,2} });
	ConstraintGroup cg1;
	bool successfulInsertion;
	successfulInsertion = cg1.addConstraint(c1);
	EXPECT_TRUE(successfulInsertion);

	//adding constraints to a non-empty constraint group
	Constraint c2(1, { {0,2},{1,2},{2,2} });
	Constraint c3(2, { {3,0},{3,1},{3,2},{2,2},{1,2} });
	successfulInsertion = cg1.addConstraint(c2);
	EXPECT_TRUE(successfulInsertion);
	successfulInsertion = cg1.addConstraint(c3);
	EXPECT_TRUE(successfulInsertion);

	//adding a constraint to a non-empty constraint group - no common variable exists
	Constraint c4(2, { {7,7},{5,8},{9,3},{10,16},{11,3} });
	successfulInsertion = cg1.addConstraint(c4);
	EXPECT_FALSE(successfulInsertion);

	//test if all constraints were added and the set of variables is updated
	std::vector<Constraint> constraints = cg1.getConstraints();
	EXPECT_TRUE(constraints.size() == 3);

	std::vector<std::pair<int, int>> allVariables = cg1.getAllVariables();
	std::vector<std::pair<int, int>> allVariablesTest = { {0,2},{1,2},{2,2},{3,0},{3,1},{3,2} };
	
	EXPECT_EQ(allVariables, allVariablesTest);
}

TEST(ConstraintGroup, isValidAssignment) {

	//valid and complete assignment
	ConstraintGroup cg1;
	Constraint c1(1, { {0,2},{1,2} });
	Constraint c2(1, { {0,2},{1,2},{2,2} });
	Constraint c3(2, { {3,0},{3,1},{3,2},{2,2},{1,2} });
	cg1.addConstraint(c1);
	cg1.addConstraint(c2);
	cg1.addConstraint(c3);

	Solution s1 = { {{0,2},{1,2},{2,2},{3,0},{3,1},{3,2}}, {0,1,0,0,1,0} };
	bool validAssignment = cg1.isValidAssignment(s1);
	EXPECT_TRUE(validAssignment);

	//the solution can contain more variables than the constraints have,
	//and it can contain less values and still be a valid solution
	Solution s2 = { {{0,2},{1,2},{2,2},{3,0},{11,11},{12,12},{3,1},{3,2}}, {0,1,0,0,1,0} };
	bool validAssignment2 = cg1.isValidAssignment(s2);
	EXPECT_TRUE(validAssignment2);

	//this solution violates the second constraint
	Solution s3 = { {{0,2},{1,2},{2,2},{3,0},{3,1},{3,2}}, {0,1,1} };
	bool validAssignment3 = cg1.isValidAssignment(s3);
	EXPECT_FALSE(validAssignment3);
}

TEST(ConstraintGroup, isCompleteAssignment) {

	//valid and complete assignment
	ConstraintGroup cg1;
	Constraint c1(1, { {0,2},{1,2} });
	Constraint c2(1, { {0,2},{1,2},{2,2} });
	Constraint c3(2, { {3,0},{3,1},{3,2},{2,2},{1,2} });
	cg1.addConstraint(c1);
	cg1.addConstraint(c2);
	cg1.addConstraint(c3);

	Solution s1 = { {{0,2},{1,2},{2,2},{3,0},{3,1},{3,2}}, {0,1,0,0,1,0} };
	bool completeAssignment = cg1.isCompleteAssignment(s1);
	EXPECT_TRUE(completeAssignment);

	//the solution can contain more variables than the constraint has,
	//but it has to have a value ordered to every variable a constraint has
	Solution s2 = { {{0,2},{1,2},{2,2},{3,0},{11,11},{12,12},{3,1},{3,2},{13,13} }, {1,1,1,1,1,1,1,1} };
	bool completeAssignment2 = cg1.isCompleteAssignment(s2);
	EXPECT_TRUE(completeAssignment2);

	//this solution doesn't have a value ordered to {3,2} variable
	Solution s3 = { {{0,2},{1,2},{2,2},{3,0},{3,1},{3,2}}, {1,1,1,1,1} };
	bool completeAssignment3 = cg1.isCompleteAssignment(s3);
	EXPECT_FALSE(completeAssignment3);
}

TEST(ConstraintGroup, haveCommonVariable) {

	//the two constraint groups have a common variable
	Constraint c1(1, { {0,2},{1,2},{2,2} });
	Constraint c2(2, { {3,0},{3,1},{1,2},{3,2} });

	Constraint c3(2, { {6,6},{7,7},{8,8} });
	Constraint c4(2, { {7,7},{3,0} });

	bool successfulInsertion;

	ConstraintGroup cg1;
	successfulInsertion = cg1.addConstraint(c1);
	EXPECT_TRUE(successfulInsertion);
	successfulInsertion = cg1.addConstraint(c2);
	EXPECT_TRUE(successfulInsertion);

	ConstraintGroup cg2;
	successfulInsertion = cg2.addConstraint(c3);
	EXPECT_TRUE(successfulInsertion);
	successfulInsertion = cg2.addConstraint(c4);
	EXPECT_TRUE(successfulInsertion);

	bool haveCommonVar = ConstraintGroup::haveCommonVariable(cg1, cg2);
	EXPECT_TRUE(haveCommonVar);

	//the two constraint groups have no common variable
	ConstraintGroup cg3;
	successfulInsertion = cg3.addConstraint(c1);
	EXPECT_TRUE(successfulInsertion);
	successfulInsertion = cg3.addConstraint(c2);
	EXPECT_TRUE(successfulInsertion);

	ConstraintGroup cg4;
	successfulInsertion = cg4.addConstraint(c3);
	EXPECT_TRUE(successfulInsertion);

	haveCommonVar = ConstraintGroup::haveCommonVariable(cg3, cg4);
	EXPECT_FALSE(haveCommonVar);
}