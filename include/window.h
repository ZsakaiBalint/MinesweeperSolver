#pragma once

#include <Windows.h>
#include <string>
#include <gdiplus.h>
#include <vector>
#include <thread>

#include "screenReader.h"
#include "clicker.h"
#include "difficulty.h"
#include "buttonHandler.h"
#include "guiData.h"

class Window {
public:
    Window();
    ~Window();
    void RunMessageLoop();
    void logMessage(const std::string& message);
    void paintMatrix(Gdiplus::Graphics& gf);
    void paintBackground(Gdiplus::Graphics& gf, PAINTSTRUCT& ps);
    int CountWindowsWithClassName(const char* className);
    bool checkMinesweeperWindows();
    RECT getMinesweeperRect();
    void handleButtonClick(int buttonID);
    HWND getDrawArea();
    void moveMinesweeperWindow();
    bool IsMinesweeperPartiallyInViewport();

    bool checkMinesweeperIllegalLocation();
    bool checkMinesweeperMinimised();
    bool checkMinesweeperClosed();

    Difficulty getDifficulty();

private:
    HWND hwnd;
    HWND hwndButton1, hwndButton2, hwndButton3; // handle to the buttons
    HWND hwndLog;                               // handle to the log control
    HWND hwndDraw;                              // handle to the draw area
    HWND hwndMinesweeper;                       // handle to minesweeper window

    ButtonHandler buttonHandler;
    GuiData guiData;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
};