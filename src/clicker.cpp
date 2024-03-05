#include "clicker.h"

void Clicker::moveCursorAndClick(int rowIndex, int colIndex) const {

    RECT minesweeperWindow;
    GetWindowRect(minesweeperHandle, &minesweeperWindow);

    int pointX = minesweeperWindow.left + 15 + (colIndex*16) + 8;
    int pointY = minesweeperWindow.top + 101 + (rowIndex*16) + 8;

    SetCursorPos(pointX,pointY);

    // Perform a left mouse button down and up event
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}

void Clicker::moveCursorAndFlag(int rowIndex, int colIndex) const {

    RECT minesweeperWindow;
    GetWindowRect(minesweeperHandle, &minesweeperWindow);

    int pointX = minesweeperWindow.left + 15 + (colIndex * 16) + 8;
    int pointY = minesweeperWindow.top + 101 + (rowIndex * 16) + 8;

    SetCursorPos(pointX, pointY);

    // Perform a left mouse button down and up event
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void Clicker::moveCursorAndClickNewGame() const {

    RECT minesweeperWindow;
    GetWindowRect(minesweeperHandle, &minesweeperWindow);

    int pointX = minesweeperWindow.left;
    int pointY = minesweeperWindow.top + 75;

    if (difficulty.toString() == "BEGINNER") {
        pointX += 80;
    }
    else if (difficulty.toString() == "INTERMEDIATE") {
        pointX += 140;
    }
    else if (difficulty.toString() == "EXPERT") {
        pointX += 260;
    }

    SetCursorPos(pointX, pointY);
    
    // Perform a left mouse button down and up event
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    //click again
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}