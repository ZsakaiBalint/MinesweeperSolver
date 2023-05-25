#pragma once

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include <map>

class Equation {
    public:
        Equation();
        Equation(int leftSide,std::vector<std::pair<int,int>> unknownCells);
        bool isAFN();
        bool isAMN();
        bool isTrivial();
        bool isSubsetOf(Equation superset);
        bool isSupersetOf(Equation subset);
        void removeVar(std::pair<int, int> pair);
        void reduceWith(Equation& subset);
        int getLeftSide() const;
        void put(std::initializer_list<std::pair<int, int>> pairs);
        void put(std::pair<int, int> pair);
        friend std::ostream& operator<<(std::ostream& os, const Equation& obj);
        bool areEquals(const Equation& obj);
        void setLeftSide(int num);

        bool isValidAssignment(std::vector<std::pair<int, int>> pairs, std::vector<int> values);

        bool containsVar(const std::pair<int, int>& variable);
        std::vector<std::pair<int,int>> getRightSide() const;

    private:
        int leftSide;
        std::vector<std::pair<int, int>> rightSide;

        void removeDuplicates();
};