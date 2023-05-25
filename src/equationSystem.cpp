#include "equationSystem.h"

EquationSystem::EquationSystem() {}

void EquationSystem::add(Equation e) {
    if(e.isAFN()) {} //AFN action here
    
    if(e.isAMN()) {} //AMN action here

    if(e.isTrivial()) {} //trivial action here

    for (int i = 0; i < equations.size(); ++i) {
        equations[i].reduceWith(e);
        e.reduceWith(equations[i]);
    }

    equations.push_back(e);
}
        
void EquationSystem::solve(){
    if(equations.size() == 0) {throw std::invalid_argument("Assigned val must be 0 or 1");}
    
    //get all variables in every equation
    for (size_t i = 0; i < equations.size(); ++i) {
 
        std::vector<std::pair<int,int>> rightSide = equations[i].getRightSide();
            
        for (size_t j = 0; j < rightSide.size(); ++j) {
            allVariables.insert(rightSide[j]);
        }
    }
    
    
    std::cout << "varibales size: " << allVariables.size() << std::endl;
    for (const auto& element : allVariables) {
        std::cout << element.first << "," << element.second << std::endl;
    }

    


}

void recursiveSolve() {
    
}

int EquationSystem::countVarOccurence(const std::pair<int, int>& variable) {
    int occurences = 0;
    for (size_t i = 0; i < equations.size(); i++) {
        if(equations[i].containsVar(variable)) {
            occurences++;
        }
    }
    return occurences;
}

int main() {
    EquationSystem e;
    Equation e1(1,{{0,3},{1,3}});               e.add(e1);
    Equation e2(2,{{0,3},{1,3},{2,3}});         e.add(e2);
    Equation e3(2,{{1,3},{2,3},{3,3}});         e.add(e3);
    Equation e4(1,{{2,3},{3,3},{4,3}});         e.add(e4);
    Equation e5(1,{{3,3},{4,3},{5,3},{5,2}});   e.add(e5);
    Equation e6(1,{{5,2}});                     e.add(e6);
    Equation e7(2,{{5,2},{6,2},{6,1},{6,0}});   e.add(e7);
    Equation e8(1,{{6,0},{6,1}});               e.add(e8);

    e.solve();

    return 0;
}