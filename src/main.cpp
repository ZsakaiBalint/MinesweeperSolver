#include "window.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR lpCmdLine, int nCmdShow)
{
    Window window;
    window.RunMessageLoop();

    return 0;
}