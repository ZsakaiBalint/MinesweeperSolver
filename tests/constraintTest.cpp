#include "pch.h"
#include "../src/constraint.cpp"

TEST(Constraint, isCompleteAssignment) {
	//every variable and corresponding values are present in the solution
	Constraint c1( 1, {{0,2},{1,2},{6,6}} );
	Solution s1( {{0,2},{6,6},{3,3},{1,2},{7,7},{8,8}}, {1,0,1,1} );
	bool complete1 = c1.isCompleteAssignment(s1);
	EXPECT_TRUE(complete1);
	
	//a variable is not present in the solution (1,2)
	Constraint c2( 1, {{0,2},{1,2},{6,6}} );
	Solution s2( {{0,2},{3,3},{6,6},{7,7},{8,8}}, {1,0,1,1} );
	bool complete2 = c2.isCompleteAssignment(s2);
	EXPECT_FALSE(complete2);

	//a corresponding value is not present in the solution for (1,2)
	Constraint c3(1, { {0,2},{1,2},{6,6} });
	Solution s3({ {0,2},{3,3},{6,6},{7,7},{8,8},{1,2} }, {1,0,1} );
	bool complete3 = c3.isCompleteAssignment(s3);
	EXPECT_FALSE(complete3);
}

TEST(Constraint, isValidAssignment) {
	//all values are assigned, which are equal to the sum
	Constraint c1(2, { {0,2},{1,2},{6,6} });
	Solution s1({ {0,2},{6,6},{3,3},{1,2},{7,7},{8,8} }, { 1,0,0,1,1 });
	bool valid1 = c1.isValidAssignment(s1);
	EXPECT_TRUE(valid1);

	//all values are assigned, which are more than the sum
	Constraint c2(2, { {0,2},{1,2},{6,6} });
	Solution s2({ {0,2},{6,6},{3,3},{1,2},{7,7},{8,8} }, { 1,1,0,1,1 });
	bool valid2 = c2.isValidAssignment(s2);
	EXPECT_FALSE(valid2);

	//all values are assigned, which are less than the sum
	Constraint c3( 2, {{0,2},{1,2},{6,6}} );
	Solution s3( {{0,2},{6,6},{3,3},{1,2},{7,7},{8,8}}, {0,1,0,0,1} );
	bool valid3 = c3.isValidAssignment(s3);
	EXPECT_FALSE(valid3);

	//not all values are assigned, but the solution can still be valid (it did not exceed the sum)
	Constraint c4(1, { {0,2},{1,2},{6,6} });
	Solution s4({ {0,2},{6,6},{3,3},{1,2},{7,7},{8,8} }, {0,1} );
	bool valid4 = c4.isValidAssignment(s4);
	EXPECT_TRUE(valid4);

	//not all values are assigned, and the solution can not be valid (it exceeded the sum)
	Constraint c5(1, {{0,2},{1,2},{6,6}} );
	Solution s5( {{0,2},{6,6},{3,3},{1,2},{7,7},{8,8}}, {1,1} );
	bool valid5 = c5.isValidAssignment(s5);
	EXPECT_FALSE(valid5);
}

TEST(Constraint, containsVar) {
	//the constraint contains the variable
	Constraint c1(1, { {0,2},{1,2},{6,6} });
	bool contains1 = c1.containsVar({ 1,2 });
	EXPECT_TRUE(contains1);

	//the constraint does not contain the variable
	Constraint c2(1, { {0,2},{1,2},{6,6} });
	bool contains2 = c2.containsVar({ 8,9 });
	EXPECT_FALSE(contains2);
}

TEST(Constraint, equality) {
	//the two constraints are equal
	Constraint c1(1, { {0,2},{1,2},{6,6} });
	Constraint c2(1, { {0,2},{1,2},{6,6} });
	bool equal1 = c1 == c2;
	EXPECT_TRUE(equal1);

	//the two constraints' variables are not in the same order (but they are the same)
	Constraint c3(1, { {0,2},{1,2},{6,6} });
	Constraint c4(1, { {1,2},{6,6},{0,2} });
	bool equal2 = c3 == c4;
	EXPECT_TRUE(equal2);

	//the two constraints are different
	Constraint c5(2, { {1,1},{2,2},{3,3} });
	Constraint c6(3, { {1,2},{6,6},{11,22},{5,5}, } );
	bool equal3 = c5 == c6;
	EXPECT_FALSE(equal3);
}

TEST(Constraint, isSubsetOf) {
	Constraint c1( 1, { {0,0},{0,1} });
	Constraint c2( 1, { {0,0},{0,1},{1,0} });

	bool isSubset = Constraint::isSubsetOf(c1,c2);
	EXPECT_TRUE(isSubset);

	bool isSubset2 = Constraint::isSubsetOf(c2, c1);
	EXPECT_FALSE(isSubset2);

	Constraint c3(1, { {4,4},{5,5},{6,6},{7,7} });
	bool isSubset3 = Constraint::isSubsetOf(c1, c3);
	EXPECT_FALSE(isSubset3);

	bool isSubset4 = Constraint::isSubsetOf(c3, c3);
	EXPECT_FALSE(isSubset4);
}

TEST(Constraint, reduce) {
	//the first constraint is the superset
	Constraint c1(1, { {0,0},{0,1},{1,0} });
	Constraint c2(1, { {0,0},{0,1} });
	
	Constraint reducedSuperset(0, { {1,0} });
	Constraint sameSubset(c2);

	Constraint::reduce(c1, c2);

	std::cerr << c1 << std::endl;
	std::cerr << c2 << std::endl;
	std::cerr << reducedSuperset << std::endl;
	std::cerr << sameSubset << std::endl;

	EXPECT_TRUE(c1 == reducedSuperset);
	EXPECT_TRUE(c2 == sameSubset);

	//the second constraint is the superset
	Constraint c3(1, { {0,0},{0,1} });
	Constraint c4(1, { {0,0},{0,1},{1,0} });

	Constraint reducedSuperset2(0, { {1,0} });
	Constraint sameSubset2(c3);

	Constraint::reduce(c3, c4);
	EXPECT_TRUE(c4 == reducedSuperset2);
	EXPECT_TRUE(c3 == sameSubset2);

	//the two constraints are not in the same coupled subset
	Constraint c5(2, { {6,6},{7,7},{8,8} });
	Constraint c6(3, { {9,9},{10,10},{11,11},{12,12} });

	Constraint noChange(c5);
	Constraint noChange2(c6);

	Constraint::reduce(c5, c6);
	EXPECT_TRUE(c5 == noChange);
	EXPECT_TRUE(c6 == noChange2);
}