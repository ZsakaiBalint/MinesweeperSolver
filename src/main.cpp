#include <iostream>
#include <string>
#include <thread>
#include "window.h"

int main() {

    std::cout << "Creating Window\n";
    MyWindow* pWindow = new MyWindow();

    bool running = true;
    while(running)
    {
        pWindow->resize();
        running = pWindow->isMinesweeperOpen();

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