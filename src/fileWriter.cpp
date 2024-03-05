#include "fileWriter.h"

void FileWriter::saveResult(Difficulty difficulty, int numberOfGuesses, bool isWon) {
    std::ifstream inputFile("tests.csv");
    bool fileExists = inputFile.good();
    inputFile.close();

    std::ofstream outputFile("tests.csv", std::ios::app); // Open the file in append mode

    if (outputFile.is_open()) {
        // File exists, so write the data
        if (!fileExists) {
            outputFile << "DIFFICULTY, NUMBER OF GUESSES, IS WON" << std::endl; //columns
        }
        outputFile << difficulty.toString() << ", " << numberOfGuesses << ", " << (isWon ? "TRUE" : "FALSE") << std::endl;
        outputFile.close();
    }
}