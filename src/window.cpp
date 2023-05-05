#include <iostream>
#include "window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{

    switch (uMsg) 
    {
        case WM_CREATE:
            break;
        
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

MyWindow::MyWindow() 
    : m_hInstance(GetModuleHandle(nullptr))
{
    minesweeperHandle = new MinesweeperHandle();
    m_isRunning = true;

    LPCSTR CLASS_NAME = "Balint Window Class"; 

    WNDCLASS wndClass = {};
    wndClass.lpszClassName = CLASS_NAME;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.lpfnWndProc = WindowProc;

    RegisterClass(&wndClass);

    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    int width = 640;
    int height = 480;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false);

    m_hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Minesweeper Solver",
        style,
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        NULL,
        NULL,
        m_hInstance,
        NULL
    );

    ShowWindow(m_hWnd, SW_SHOW);
}

MyWindow::~MyWindow() 
{
    m_isRunning = false;

    LPCSTR CLASS_NAME = "Balint Window Class";

    UnregisterClass(CLASS_NAME, m_hInstance);

    delete minesweeperHandle;
}

bool MyWindow::processMessages() 
{
    MSG msg = {};

    while(PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

MinesweeperHandle* MyWindow::getMinesweeperHandle() {
    return minesweeperHandle;
}

HWND MyWindow::getHandler() {
    return m_hWnd;
}

bool MyWindow::isRunning(){
    return m_isRunning;
}

void MyWindow::resize(){
    RECT rect = minesweeperHandle->getMinesweeperRect();
    std::cout << "RECT: left=" << rect.left << ", top=" << rect.top << ", right=" << rect.right << ", bottom=" << rect.bottom << std::endl;
    SetWindowPos(m_hWnd, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
}