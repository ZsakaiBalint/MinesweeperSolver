#include "window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, int nCmdShow)
{
    try {
        Window window;
        window.RunMessageLoop();
    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;
        MessageBoxA(NULL, e.what(), "EXCEPTION", MB_OK);
        return 1; // Indicate failure
    }
    catch (...) {
        std::cerr << "An unknown exception occurred." << std::endl;
        MessageBoxA(NULL, "UNKNOWN EXCEPTION", "UNKNOWN EXCEPTION", MB_OK);
        return 1; // Indicate failure
    }

    return 0;
}