#include <stdexcept>
#include "minesweeperHandle.h"

//Find the minesweeper window
//Throw an exception if no minesweeper window is found
//Throw an exception if multiple minesweeper windows are found
MinesweeperHandle::MinesweeperHandle(){
    minesweeperWindowHandle = NULL;

    bool found = false;
    int minesweeperInstanceCount = 0;

    //iterate over all open windows' title
    HWND currentWindowHandle = NULL;
    while ((currentWindowHandle = FindWindowEx(NULL, currentWindowHandle, NULL, NULL)) != NULL) {

        LPSTR currentWindowName = new char[256];
        GetWindowText(currentWindowHandle, currentWindowName, 256);

        // Check if the window title contains "Microsoft Minesweeper"
        if (strstr(currentWindowName, "Microsoft Minesweeper") != NULL) {
            minesweeperWindowHandle = currentWindowHandle;
            found = true;
            minesweeperInstanceCount++;
        }
    }

    //throw an exception if necessary
    if(!found){
        throw std::runtime_error("No Microsoft Minesweeper instance was found.");
    }
    if(minesweeperInstanceCount > 1){
        throw std::runtime_error("Multiple Microsoft Minesweeper instances were found.");
    }

}

MinesweeperHandle::~MinesweeperHandle(){
    
}

//Check if the minesweeper window is open and visible
bool MinesweeperHandle::isMinesweeperOpen() {
    bool open = IsWindow(minesweeperWindowHandle) && IsWindowVisible(minesweeperWindowHandle);
    return open;
}

//Get the area of the minesweeper window
RECT MinesweeperHandle::getMinesweeperRect(){
    RECT rect = { 0 };
    GetWindowRect(minesweeperWindowHandle, &rect);
    return rect;
}