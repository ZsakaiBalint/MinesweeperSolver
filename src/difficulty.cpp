#include "difficulty.h"

std::string Difficulty::toString() const {
    return this->stringRepresentation;
}

int Difficulty::getWidth() const {
    return this->minefieldWidth;
}

int Difficulty::getHeight() const {
    return this->minefieldHeight;
}

int Difficulty::getNumberOfMines() const {
    return this->numberOfMines;
}