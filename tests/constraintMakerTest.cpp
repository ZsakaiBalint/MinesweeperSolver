#include "pch.h"
#include "../src/constraintMaker.cpp"

TEST(ConstraintMaker, convertMinefieldToConstraints) {

	//2x2 minefield
	std::vector<std::vector<Square>> minefield1 = {
		{TWO,		UNKNOWN},
		{UNKNOWN,	FLAGGED},
	};

	ConstraintMaker csm1(minefield1);
	std::vector<Constraint> constraints11 = csm1.getAllConstraints();
	std::vector<Constraint> constraints12;
	constraints12.push_back(Constraint(1, { {0,1},{1,0} }));

	for (int i = 0; i < constraints12.size(); ++i) {
		Constraint c1 = constraints11[i];
		Constraint c2 = constraints12[i];
		EXPECT_TRUE(c1 == c2);
	}

	//3x3 minefield
	std::vector<std::vector<Square>> minefield2 = {
		{UNKNOWN,	UNKNOWN,	UNKNOWN},
		{UNKNOWN,	THREE,		FLAGGED},
		{UNKNOWN,	ONE,		UNKNOWN},
	};

	ConstraintMaker csm2(minefield2);
	std::vector<Constraint> constraints21 = csm2.getAllConstraints();
	std::vector<Constraint> constraints22;
	constraints22.push_back(Constraint(2, { {0,0},{0,1},{0,2},{1,0},{2,0},{2,2} }));

	for (int i = 0; i < constraints21.size(); ++i) {
		Constraint c1 = constraints21[i];
		Constraint c2 = constraints22[i];
		EXPECT_TRUE(c1 == c2);
	}

	//4x4 minefield
	std::vector<std::vector<Square>> minefield3 = {
		{ZERO,		ZERO,		ZERO,		ZERO},
		{UNKNOWN,	UNKNOWN,	TWO,		ZERO},
		{UNKNOWN,	UNKNOWN,	THREE,		ONE},
		{UNKNOWN,	FLAGGED,	UNKNOWN,	UNKNOWN},
	};

	ConstraintMaker csm3(minefield3);
	std::vector<Constraint> constraints31 = csm3.getAllConstraints();
	std::vector<Constraint> constraints32;
	constraints32.push_back(Constraint(2, { {1,1},{2,1} }));
	constraints32.push_back(Constraint(2, { {1,1},{2,1},{3,2},{3,3} }));
	constraints32.push_back(Constraint(1, { {3,2},{3,3} }));

	for (int i = 0; i < constraints31.size(); ++i) {
		Constraint c1 = constraints31[i];
		Constraint c2 = constraints32[i];
		EXPECT_TRUE(c1 == c2);
	}
}

TEST(ConstraintMaker, groupConstraints) {

	//the groupConstraints function works well with the read minefield
	std::vector<std::vector<Square>> minefield = {
		{UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN},
		{UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN},
		{UNKNOWN,TWO	,ONE	,ONE	,ONE	,TWO	,UNKNOWN,UNKNOWN},
		{FLAGGED,ONE	,ZERO	,ZERO	,ZERO	,TWO	,UNKNOWN,UNKNOWN},
		{ONE	,TWO	,ONE	,ONE	,ZERO	,ONE	,FLAGGED,UNKNOWN},
		{ZERO	,ONE	,UNKNOWN,ONE	,ZERO	,ONE	,THREE	,UNKNOWN},
		{ZERO	,ONE	,ONE	,ONE	,ZERO	,ZERO	,TWO	,UNKNOWN},
		{ZERO	,ZERO	,ZERO	,ZERO	,ZERO	,ZERO	,ONE	,UNKNOWN}
	};
	ConstraintMaker csm(minefield);
	std::vector<Constraint> constraints = csm.convertMinefieldToConstraints(minefield);
	std::vector<ConstraintGroup> groupedConstraints = csm.groupConstraints(constraints);

	ConstraintGroup cg1;
	cg1.addConstraint({ 1, {{1,1},{2,0},{1,0},{1,2}} });
	cg1.addConstraint({ 1, {{1,2},{1,1},{1,3}} });
	cg1.addConstraint({ 1, {{1,3},{1,2},{1,4}} });
	cg1.addConstraint({ 1, {{1,4},{1,3},{1,5}} });
	cg1.addConstraint({ 2, {{1,5},{2,6},{1,4},{1,6},{3,6}} });
	cg1.addConstraint({ 1, {{3,6},{2,6}} });
	EXPECT_TRUE(groupedConstraints[0] == cg1);

	ConstraintGroup cg2;
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	EXPECT_TRUE(groupedConstraints[1] == cg2);

	ConstraintGroup cg3;
	cg3.addConstraint({ 2, {{5,7},{4,7},{6,7}} });
	cg3.addConstraint({ 2, {{6,7},{5,7},{7,7}} });
	cg3.addConstraint({ 1, {{7,7},{6,7}} });
	EXPECT_TRUE(groupedConstraints[2] == cg3);

	//what happens if we have constraints that are grouped
	//in an not-so-obvious way
	std::vector<Constraint> constraints2;
	constraints2.push_back({ 1, { {1,0},{1,1},{1,2}} });				//1st group
	constraints2.push_back({ 2, { {2,0},{2,1},{2,2}} });				//1st group
	
	constraints2.push_back({ 1, { {100,100},{101,101}} });				//2nd group

	constraints2.push_back({ 1, { {10,10},{10,11},{10,12}} });			//1st group
	constraints2.push_back({ 2, { {20,20},{20,21},{20,22}} });			//1st group

	constraints2.push_back({ 1, { {50,50},{51,51}} });					//1st group

	constraints2.push_back({ 1, { {200,200},{201,201}} });				//3rd group

	constraints2.push_back({ 1, { {1,0},{2,2},{50,50}} });				//1st group
	constraints2.push_back({ 1, { {10,10},{20,22},{51,51}} });			//1rd group

	std::vector<std::vector<Square>> emptyMinefield = { {} };
	ConstraintMaker csm2(emptyMinefield);
	std::vector<ConstraintGroup> groups = csm2.groupConstraints(constraints2);

	EXPECT_EQ(groups.size(),3);
}

TEST(ConstraintMaker, reduceConstraintGroup) {
	
	//there are multiple reductions in the constraint group
	ConstraintGroup cg;
	cg.addConstraint({ 2, {{5,5},{6,6},{7,7},{8,8}} });
	cg.addConstraint({ 3, {{8,8},{9,9},{10,10},{11,11}} });
	cg.addConstraint({ 1, {{10,10},{11,11}} });
	cg.addConstraint({ 1, {{5,5},{6,6}} });
	cg.addConstraint({ 2, {{11,11},{12,12},{13,13}} });

	ConstraintMaker::reduceConstraintGroup(cg);

	EXPECT_TRUE(cg.getConstraints().size() == 5);
	Constraint c11({ 1, {{7,7},{8,8}} });
	Constraint c12({ 2, {{8,8},{9,9}} });
	Constraint c13({ 1, {{10,10},{11,11}} });
	Constraint c14({ 1, {{5,5},{6,6}} });
	Constraint c15({ 2, {{11,11},{12,12},{13,13}} });
	EXPECT_TRUE(cg.getConstraints()[0] == c11);
	EXPECT_TRUE(cg.getConstraints()[1] == c12); 
	EXPECT_TRUE(cg.getConstraints()[2] == c13); 
	EXPECT_TRUE(cg.getConstraints()[3] == c14); 
	EXPECT_TRUE(cg.getConstraints()[4] == c15);

	//there are no reductions in the constraint group
	ConstraintGroup cg2;
	cg2.addConstraint({ 2, {{1,1},{2,2},{3,3},{100,100}} });
	cg2.addConstraint({ 2, {{4,4},{5,5},{6,6},{100,100}} });
	cg2.addConstraint({ 2, {{7,7},{8,8},{9,9},{10,10},{100,100}} });
	cg2.addConstraint({ 2, {{11,11},{12,12},{100,100}} });
	cg2.addConstraint({ 2, {{13,13},{100,100}} });

	ConstraintMaker::reduceConstraintGroup(cg2);

	ConstraintGroup reducedGroupTest2;
	reducedGroupTest2.addConstraint({ 2, {{1,1},{2,2},{3,3},{100,100}} });
	reducedGroupTest2.addConstraint({ 2, {{4,4},{5,5},{6,6},{100,100}} });
	reducedGroupTest2.addConstraint({ 2, {{7,7},{8,8},{9,9},{10,10},{100,100}} });
	reducedGroupTest2.addConstraint({ 2, {{11,11},{12,12},{100,100}} });
	reducedGroupTest2.addConstraint({ 2, {{13,13},{100,100}} });

	EXPECT_TRUE(cg2 == reducedGroupTest2);

	//there is only a single reduction
	//(constraints and variables are not deleted)
	ConstraintGroup cg3;
	cg3.addConstraint({ 1, {{1,1},{2,2},{3,3}} });
	cg3.addConstraint({ 1, {{1,1},{2,2}} });

	ConstraintMaker::reduceConstraintGroup(cg3);

	EXPECT_TRUE(cg3.getConstraints().size() == 2);
	Constraint c31({ 0, { { {3,3}} } });
	Constraint c32({ 1, { { {1,1},{2,2}} } });
	EXPECT_TRUE(cg3.getConstraints()[0] == c31);
	EXPECT_TRUE(cg3.getConstraints()[1] == c32);
	std::vector<std::pair<int, int>> cg3Vars = { {1,1},{2,2},{3,3} };
	EXPECT_EQ(cg3.getAllVariables(), cg3Vars);
}

TEST(ConstraintMaker, calculateMinefreeSquares) {
	//3x3 minefield
	std::vector<std::vector<Square>> minefield = {
		{ZERO   ,	UNKNOWN,	FLAGGED},
		{UNKNOWN,	ONE    ,	UNKNOWN},
		{UNKNOWN,	ZERO   ,	UNKNOWN},
	};

	ConstraintMaker csm(minefield);
	std::vector<std::pair<int, int>> minefreeSquares = csm.calculateMinefreeSquares(minefield);
	std::vector<std::pair<int, int>> minefreeSquaresTest = { {0,1}, {1,0}, {1,2}, {2,0}, {2,2} };

	EXPECT_EQ(minefreeSquares, minefreeSquaresTest);
}

TEST(ConstraintMaker, calculateMineSquares) {

	std::vector<std::vector<Square>> minefield = {
		{UNKNOWN,	UNKNOWN,	FLAGGED},
		{ZERO	,	THREE  ,	ZERO   },
		{ZERO	,	ZERO   ,	ZERO   },
	};

	ConstraintMaker csm(minefield);
	std::vector<std::pair<int, int>> mineSquares = csm.calculateMineSquares(minefield);
	std::vector<std::pair<int, int>> mineSquaresTest = { {0,0}, {0,1} };

	EXPECT_EQ(mineSquares, mineSquaresTest);

	//there can be cases where 2 squares give the same result: that a third square is a mine
	//in this case, the return vector only contains the duplicate element once

	std::vector<std::vector<Square>> minefield1 = {
	{ZERO	,	ZERO	,	ZERO	},
	{ZERO	,	ONE    ,	ONE	   },
	{ZERO	,	ZERO,		UNKNOWN},
	};

	ConstraintMaker csm1(minefield1);
	std::vector<std::pair<int, int>> mineSquares1 = csm1.calculateMineSquares(minefield1);
	std::vector<std::pair<int, int>> mineSquaresTest1 = { {2,2} };

	EXPECT_EQ(mineSquares1, mineSquaresTest1);
}