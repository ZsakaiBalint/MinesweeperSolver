#include "pch.h"
#include "../src/constraintGroupSolver.cpp"
TEST(ConstraintGroupSolver, solve) {

	//constraint group with different constraints
	ConstraintGroup reducedGroup;
	reducedGroup.addConstraint({ 1, {{1,1},{2,0},{1,0},{1,2}} });
	reducedGroup.addConstraint({ 1, {{1,2},{1,1},{1,3}} });
	reducedGroup.addConstraint({ 1, {{1,3},{1,2},{1,4}} });
	reducedGroup.addConstraint({ 1, {{1,4},{1,3},{1,5}} });
	reducedGroup.addConstraint({ 2, {{1,5},{2,6},{1,4},{1,6},{3,6}} });
	reducedGroup.addConstraint({ 1, {{3,6},{2,6}} });

	ConstraintGroupSolver solver(reducedGroup);
	solver.solve();

	SolutionMatrix sm1 = solver.getSolutionMatrix();

	std::vector<std::pair<int, int>> allVariables = { {1,1},{1,4},{3,6},{2,6},{2,0},{1,3},{1,6},{1,0},{1,2},{1,5} };
	std::vector<std::vector<int>> allValues = {
		{0, 0, 1, 0, 0, 1, 1, 1, 0, 0,},
		{0, 0, 0, 1, 0, 1, 1, 1, 0, 0,},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 1,},
		{0, 0, 0, 1, 0, 0, 0, 0, 1, 1,},
		{1, 1, 1, 0, 0, 0, 0, 0, 0, 0,},
		{1, 1, 0, 1, 0, 0, 0, 0, 0, 0,},
		{0, 0, 1, 0, 1, 1, 1, 0, 0, 0,},
		{0, 0, 0, 1, 1, 1, 1, 0, 0, 0,}
	};
	SolutionMatrix sm2(allVariables, allValues);

	EXPECT_TRUE(sm1 == sm2);

	//solution group with same constraints
	ConstraintGroup cg2;
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });
	cg2.addConstraint({ 1, {{5,2}} });

	ConstraintGroupSolver solver2(cg2);
	solver2.solve();
	SolutionMatrix sm3 = solver2.getSolutionMatrix();

	std::vector<std::pair<int, int>> allVariables2 = { {5,2} };
	std::vector<std::vector<int>> allValues2 = { {1} };
	SolutionMatrix sm4(allVariables2, allValues2);

	EXPECT_TRUE(sm3 == sm4);

}