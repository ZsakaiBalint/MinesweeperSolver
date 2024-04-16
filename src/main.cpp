#include "window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, int nCmdShow)
{
    try {
        Window window;
        window.RunMessageLoop();
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        return 1; // Indicate failure
    }
    catch (...) {
        std::cerr << "An unknown exception occurred." << std::endl;
        return 1; // Indicate failure
    }

    return 0;
}