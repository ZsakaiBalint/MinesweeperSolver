#include <iostream>
#include <string>

#include "window.h"

using namespace std;

HWND g_hwndMinesweeper = NULL;

bool isMinesweeperOpen() {
    bool found = false;
    HWND hwnd = NULL;

    // Iterate over all open windows
    while ((hwnd = FindWindowEx(NULL, hwnd, NULL, NULL)) != NULL) {
        LPSTR currentWindowName = new char[256];
        GetWindowText(hwnd, currentWindowName, 256);

        // Check if the window title contains "Microsoft Minesweeper"
        if (strstr(currentWindowName, "Microsoft Minesweeper") != NULL) {
            g_hwndMinesweeper = hwnd;
            found = true;
            break;
        }
    }

    return found;
}

RECT getMinesweeperRect(){
    RECT rect = { 0 };
    GetClientRect(g_hwndMinesweeper, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    std::cout << "Client area size: " << width << " x " << height << std::endl;

    return rect;
}

int main() {

    if (isMinesweeperOpen()) {
        cout << "Microsoft Minesweeper is open." << endl;
        getMinesweeperRect();
    } else {
        cout << "Microsoft Minesweeper is not open." << endl;
    }






    std::cout << "Creating Window\n";
    MyWindow* pWindow = new MyWindow();
    bool running = true;
    while(running)
    {
        if (!pWindow->processMessages())
        {
            std::cout << "Closing Window\n";
            running = false;
        }

        Sleep(10);
    }

    delete pWindow;

   

    return 0;
}