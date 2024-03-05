#pragma once

#include <string>

class Difficulty {
protected:
	int minefieldWidth;
	int minefieldHeight;
	int numberOfMines;
	std::string stringRepresentation;
public:
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual int getNumberOfMines() const;
	virtual std::string toString() const;
	Difficulty(int width, int height, int mines, std::string name) : minefieldWidth(width), minefieldHeight(height), numberOfMines(mines), stringRepresentation(name) {}
	Difficulty(const Difficulty& other) : minefieldWidth(other.minefieldWidth),minefieldHeight(other.minefieldHeight),numberOfMines(other.numberOfMines),stringRepresentation(other.stringRepresentation) {}
	Difficulty() : minefieldWidth(-1), minefieldHeight(-1), numberOfMines(-1), stringRepresentation("?!") {}
};

class Beginner : public Difficulty {
public:
	Beginner() : Difficulty(8, 8, 10, "BEGINNER") {};
};

class Intermediate : public Difficulty {
public:
	Intermediate() : Difficulty(16, 16, 40, "INTERMEDIATE") {};
};

class Expert : public Difficulty {
public:
	Expert() : Difficulty(30, 16, 99, "EXPERT") {};
};