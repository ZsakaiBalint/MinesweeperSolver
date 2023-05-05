#pragma once
#include <Windows.h>
#include "minesweeperHandle.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class MyWindow {

  public:
    MyWindow();
    MyWindow(const MyWindow&) = delete;
    MyWindow& operator = (const MyWindow&) = delete;
    ~MyWindow();
    bool processMessages();
    void resize();
    MinesweeperHandle* getMinesweeperHandle();
    HWND getHandler();
    bool isRunning();

  private:
    HINSTANCE m_hInstance;
    HWND m_hWnd;
    MinesweeperHandle* minesweeperHandle;
    bool m_isRunning;
};
