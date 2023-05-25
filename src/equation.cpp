#include "equation.h"

Equation::Equation() {
    leftSide = 0;
}

Equation::Equation(int leftSide,std::vector<std::pair<int,int>> rightSide) {
    this->leftSide = leftSide;
    this->rightSide = rightSide;
}

//check for all-free-neighbors
bool Equation::isAFN() { 
    return leftSide == 0;
};
//check for all-mine-neighbors
bool Equation::isAMN() { 
    return (leftSide != 0) && (leftSide == rightSide.size());
}
//check for trivial constraints
bool Equation::isTrivial() {
    return rightSide.size() == 1;
}

bool Equation::isSubsetOf(Equation superset) {
    return std::includes(superset.rightSide.begin(), superset.rightSide.end(), this->rightSide.begin(), this->rightSide.end());
}

bool Equation::isSupersetOf(Equation subset) {
    return std::includes(this->rightSide.begin(), this->rightSide.end(), subset.rightSide.begin(), subset.rightSide.end());
}

//remove a variable from the equation
void Equation::removeVar(std::pair<int, int> pair) {
    rightSide.erase(std::remove(rightSide.begin(), rightSide.end(), pair), rightSide.end());
}

//reduce one equation with one of it's subsets
void Equation::reduceWith(Equation& subset) {
    if(! this->isSupersetOf(subset)) {return;}

    setLeftSide(getLeftSide() - subset.getLeftSide());

    for (const auto& pair : getRightSide()) {
        for (const auto& pair2 : subset.getRightSide()) {
            if(pair == pair2) {
                removeVar(pair);
            }
        }
    }

}

void Equation::setLeftSide(int num) {
    leftSide = num;
}

int Equation::getLeftSide() const {
    return leftSide;
}

void Equation::put(std::initializer_list<std::pair<int, int>> pairs) {
    for (const auto& pair : pairs) {
        rightSide.push_back(pair);
    }
    removeDuplicates();
}
void Equation::put(std::pair<int, int> pair) {
    rightSide.push_back(pair);
    removeDuplicates();
}



std::ostream& operator<<(std::ostream& os, const Equation& obj) {
    os << obj.leftSide << " = ";

    int currentIndex = 0;
    for (const auto& pair : obj.getRightSide()) {
        if (currentIndex != 0) {
            os << " + ";
        }
        os << "(" << pair.first << "," << pair.second << ")";
        currentIndex++;
    }  
    return os;
}

bool Equation::areEquals(const Equation& obj){

    if(getLeftSide() != obj.getLeftSide()){return false;}

    std::vector<std::pair<int, int>> sortedVec1 = getRightSide();
    std::vector<std::pair<int, int>> sortedVec2 = obj.getRightSide();

    if (sortedVec1.size() != sortedVec2.size()) {
        return false;
    }

    // Sort the vectors based on the first element of each pair
    std::sort(sortedVec1.begin(), sortedVec1.end());
    std::sort(sortedVec2.begin(), sortedVec2.end());

    // Compare the sorted vectors element by element
    return std::equal(sortedVec1.begin(), sortedVec1.end(), sortedVec2.begin(), sortedVec2.end());
}

std::vector<std::pair<int,int>> Equation::getRightSide() const {
    return rightSide;
}

void Equation::removeDuplicates() {
    std::sort(rightSide.begin(), rightSide.end()); 
    rightSide.erase(std::unique(rightSide.begin(), rightSide.end()), rightSide.end()); 
}

bool Equation::isValidAssignment(std::vector<std::pair<int, int>> pairs, std::vector<int> values){
  if(pairs.size() != values.size()) {throw std::invalid_argument("variables and values must have the same size");}
 
  std::map<std::pair<int, int>, int> variableMap;
  
  //behelyettesítjük amit tudunk
  for(int i=0;i<pairs.size();++i) {
    if(!containsVar(pairs[i])) {continue;}
    variableMap[pairs[i]] = values[i];
  }

  //ha minden változót behelyettesítettünk
  if(variableMap.size() == rightSide.size()){
    int sum = 0;
    for(int i=0;i<rightSide.size();++i) {
        sum += variableMap[rightSide[i]];
    }
    return leftSide == sum;
  }

  //ha nem minden változót helyettesítettünk be
  else {
    int sum = 0;

    for (const auto& pair : variableMap) {
        int value = pair.second;
        sum += value;
    }

    return leftSide >= sum;
  }
}

bool Equation::containsVar(const std::pair<int, int>& variable) {
    return std::find(rightSide.begin(), rightSide.end(), variable) != rightSide.end();
}

/*
int main() {
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
   
    std::cout << e1.areEquals(e3) << std::endl;
    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;
    std::cout << e3 << std::endl;
}
*/