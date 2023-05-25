#include "../src/equation.h"

#include <stdexcept>
#include <gtest/gtest.h>

TEST(Equation_class, subset_and_superset_functions) {
    Equation e1;
    Equation e2;
    e1.setLeftSide(1);
    e1.put({{0, 1}, {2, 3}, {4, 5}});
    e2.setLeftSide(1);
    e2.put({{0, 1}, {2, 3}});

    EXPECT_TRUE(e1.isSupersetOf(e2));
    EXPECT_FALSE(e1.isSubsetOf(e2));

    EXPECT_FALSE(e2.isSupersetOf(e1));
    EXPECT_TRUE(e2.isSubsetOf(e1));
  
    EXPECT_TRUE(e1.isSupersetOf(e1));
    EXPECT_TRUE(e1.isSubsetOf(e1));
}

TEST(Equation_class, trivial_function) {
    Equation e1;
    Equation e2;
    Equation e3;

    e1.setLeftSide(0);
    e1.put({2,3});

    e2.setLeftSide(1);
    e2.put({4,2});

    e3.setLeftSide(3);
    e3.put({{2,3},{4,2}});

    EXPECT_TRUE(e1.isTrivial());
    EXPECT_TRUE(e2.isTrivial());
    EXPECT_FALSE(e3.isTrivial());
}

TEST(Equation_class, removeVar_function) {
    Equation e1;
    Equation e2;
  
    e1.setLeftSide(3);
    e1.put({{2,3},{4,2},{6,6},{1,9}});
    e1.removeVar({6,6});

    e2.setLeftSide(3);
    e2.put({{2,3},{4,2},{1,9}});

    EXPECT_EQ(e1.getRightSide(),e2.getRightSide());
}

TEST(Equation_class, reduceWith_function) {
    Equation e1;
    Equation e2;
    Equation e3;
  
    e1.setLeftSide(3);
    e1.put({{2,3},{4,2},{6,6},{1,9}});

    e2.setLeftSide(2);
    e2.put({{2,3},{4,2},{1,9}});

    e1.reduceWith(e2);

    e3.setLeftSide(1);
    e3.put({6,6});
   
    EXPECT_TRUE(e1.areEquals(e3));
}

TEST(Equation_class,AFN_and_AMN) {
    Equation e1;
    Equation e2;

    e1.setLeftSide(0);
    e2.setLeftSide(3);
    e2.put({{1,2},{2,2},{3,2}});

    EXPECT_EQ(e1.isAFN(),true);
    EXPECT_EQ(e1.isAMN(),false);

    EXPECT_EQ(e2.isAFN(),false);
    EXPECT_EQ(e2.isAMN(),true);
}

TEST(Equation_class,two_equations_are_same) {
    Equation e1;
    Equation e2;
    Equation e3;
  
    e1.setLeftSide(3);
    e1.put({{2,3},{4,2},{6,6},{1,9},{6,7}});

    e2.setLeftSide(3);
    e2.put({{6,7},{1,9},{2,3},{6,6},{4,2}});

    e3.setLeftSide(2);
    e3.put({{6,7},{2,3}});

    EXPECT_TRUE(e1.areEquals(e2));
    EXPECT_FALSE(e1.areEquals(e3));
}

TEST(Equation_class,removing_duplicates) {
    Equation e1;
    Equation e2;
  
    e1.setLeftSide(3);
    e1.put({{2,3},{4,2},{6,6}});

    e2.setLeftSide(3);
    e2.put({{6,6},{6,6},{6,6},{6,6},{4,2},{2,3}});

    EXPECT_TRUE(e1.areEquals(e2));
}

TEST(Equation_class,is_valid_assignment_function) {
    Equation e1;

    e1.setLeftSide(3);
    e1.put({{2,3},{4,2},{6,6},{5,2},{4,4}});

    std::vector<std::pair<int,int>> variables;
    std::vector<int> values;

    variables.push_back({2,3}); values.push_back(1);
    variables.push_back({4,2}); values.push_back(1);
    variables.push_back({6,6}); values.push_back(1);
    variables.push_back({5,2}); values.push_back(1);
    variables.push_back({4,4}); values.push_back(1);
    EXPECT_FALSE(e1.isValidAssignment(variables,values));

    variables.clear();values.clear();
    variables.push_back({2,3}); values.push_back(0);
    variables.push_back({4,2}); values.push_back(0);
    variables.push_back({6,6}); values.push_back(0);
    variables.push_back({5,2}); values.push_back(0);
    variables.push_back({4,4}); values.push_back(0);
    EXPECT_FALSE(e1.isValidAssignment(variables,values));

    variables.clear();values.clear();
    variables.push_back({2,3}); values.push_back(1);
    variables.push_back({4,2}); values.push_back(0);
    variables.push_back({6,6}); values.push_back(1);
    variables.push_back({5,2}); values.push_back(1);
    variables.push_back({4,4}); values.push_back(0);
    EXPECT_TRUE(e1.isValidAssignment(variables,values));

    variables.clear();values.clear();
    variables.push_back({2,3}); values.push_back(1);
    variables.push_back({4,2}); values.push_back(1);
    variables.push_back({6,6}); values.push_back(1);
    variables.push_back({5,2}); values.push_back(1);
    variables.push_back({4,4}); values.push_back(0);
    EXPECT_FALSE(e1.isValidAssignment(variables,values));

    variables.clear();values.clear();
    variables.push_back({2,3}); values.push_back(0);
    variables.push_back({4,2}); values.push_back(0);
    variables.push_back({6,6}); values.push_back(1);
    variables.push_back({5,2}); values.push_back(1);
    variables.push_back({4,4}); values.push_back(0);
    EXPECT_FALSE(e1.isValidAssignment(variables,values));

    variables.clear();values.clear();
    variables.push_back({2,3}); values.push_back(1);
    variables.push_back({5,2}); values.push_back(1);
    variables.push_back({4,4}); values.push_back(1);
    EXPECT_TRUE(e1.isValidAssignment(variables,values));

    variables.clear();values.clear();
    variables.push_back({4,2}); values.push_back(0);
    variables.push_back({6,6}); values.push_back(1);
    EXPECT_TRUE(e1.isValidAssignment(variables,values)); 

    variables.clear();values.clear();
    variables.push_back({2,3}); values.push_back(1);
    variables.push_back({6,6}); values.push_back(1);
    variables.push_back({5,2}); values.push_back(1);
    variables.push_back({4,4}); values.push_back(1);
    EXPECT_FALSE(e1.isValidAssignment(variables,values)); 

    variables.clear();values.clear();
    variables.push_back({2,3}); values.push_back(1);
    variables.push_back({6,6}); 
    variables.push_back({5,2}); 
    variables.push_back({4,4}); values.push_back(1);
    EXPECT_THROW(e1.isValidAssignment(variables,values),std::invalid_argument); 
    
    variables.clear();values.clear();
    variables.push_back({888,888}); values.push_back(0);
    variables.push_back({666,666}); values.push_back(666);
    variables.push_back({777,777}); values.push_back(1);
    variables.push_back({555,555}); values.push_back(1);
    variables.push_back({444,444}); values.push_back(1);
    variables.push_back({333,333}); values.push_back(1);
    variables.push_back({4,4}); values.push_back(0);
    variables.push_back({2,3}); values.push_back(1);
    EXPECT_TRUE(e1.isValidAssignment(variables,values));
}

TEST(Equation_class,constructor_with_args) {
    Equation e1(2,{{2,4},{4,5},{4,6}});
    Equation e2;

    e2.setLeftSide(2);
    e2.put({{2,4},{4,5},{4,6}});
  
    EXPECT_TRUE(e1.areEquals(e2));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}