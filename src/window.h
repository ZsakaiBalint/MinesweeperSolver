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
    void resize();
  
    HWND getHandler();
    bool isRunning();
    bool isMinesweeperOpen(); //checks if minesweeper is open
    RECT getMinesweeperRect(); //get the are of minsweeper
    HWND getMinesweeperHandle();
    void findMinesweeper(); //find the minesweeper window
    void doSomething(int xPos, int yPos);

  private:
    HINSTANCE m_hInstance;
    HWND m_hWnd;
    HWND minesweeperHandle;
    bool m_isRunning;
};
