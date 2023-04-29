#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class MyWindow {

  public:
    MyWindow();
    MyWindow(const MyWindow&) = delete;
    MyWindow& operator = (const MyWindow&) = delete;
    ~MyWindow();
    bool processMessages();

  private:
    HINSTANCE m_hInstance;
    HWND m_hWnd;
};
