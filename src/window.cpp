#include <iostream>
#include <WindowsX.h>
#include "window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    //Now get the handler for the minesweeper's window
    MyWindow* pMyWindow = nullptr;
    int xPos, yPos;
    
    switch (uMsg) 
    {
        case WM_LBUTTONDOWN:
            pMyWindow = (MyWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
            xPos = GET_X_LPARAM(lParam);
            yPos = GET_Y_LPARAM(lParam); 
            std::cout<<"x: " << xPos << " y: " << yPos << std::endl;
            pMyWindow->doSomething(xPos,yPos);
            break;
            
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

MyWindow::MyWindow() : m_hInstance(GetModuleHandle(nullptr))
{
    //check if the window class is already registered
    LPCSTR CLASS_NAME = "Balint Window Class";
    WNDCLASS wndClass = {};

    if (!GetClassInfo(m_hInstance, CLASS_NAME, &wndClass)){
        wndClass.lpszClassName = CLASS_NAME;
        wndClass.hInstance = m_hInstance;
        wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndClass.lpfnWndProc = WindowProc;

        RegisterClass(&wndClass);
    }

    //define the style of the window
    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    int width = 640;
    int height = 480;

    RECT rect;
    rect.left = 250;
    rect.top = 250;
    rect.right = rect.left + width;
    rect.bottom = rect.top + height;

    AdjustWindowRect(&rect, style, false);

    //create the window
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

    if (m_hWnd == NULL) {
        throw std::runtime_error("Failed to create window");
    }

    findMinesweeper();
    m_isRunning = true;

    SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), 128, LWA_ALPHA);

    SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

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

HWND MyWindow::getHandler() {
    return m_hWnd;
}

bool MyWindow::isRunning(){
    return m_isRunning;
}

void MyWindow::resize(){
    RECT rect = getMinesweeperRect();
    std::cout << "RECT: left=" << rect.left << ", top=" << rect.top << ", right=" << rect.right << ", bottom=" << rect.bottom << std::endl;
}

//Check if the minesweeper window is open and visible
bool MyWindow::isMinesweeperOpen() {
    bool open = IsWindow(minesweeperHandle) && IsWindowVisible(minesweeperHandle);
    return open;
}

//Get the area of the minesweeper window
RECT MyWindow::getMinesweeperRect(){
    RECT rect = { 0 };
    GetWindowRect(minesweeperHandle, &rect);
    return rect;
}

void MyWindow::findMinesweeper(){
    minesweeperHandle = NULL;

    bool found = false;
    int minesweeperInstanceCount = 0;

    //iterate over all open windows' title
    HWND currentWindowHandle = NULL;
    while ((currentWindowHandle = FindWindowEx(NULL, currentWindowHandle, NULL, NULL)) != NULL) {

        LPSTR currentWindowName = new char[256];
        GetWindowText(currentWindowHandle, currentWindowName, 256);

        std::cout<<currentWindowHandle<<std::endl;

        // Check if the window title contains "Microsoft Minesweeper"
        if (strstr(currentWindowName, "Minesweeper X") != NULL) {
            
            minesweeperHandle = currentWindowHandle;
            found = true;
            //minesweeperInstanceCount++;
        }
    }

    //throw an exception if necessary
    if(!found){
        throw std::runtime_error("No Minesweeper X instance was found.");
    }
    //if(minesweeperInstanceCount > 1){
    //    throw std::runtime_error("Multiple Microsoft Minesweeper instances were found.");
    //}
}

HWND MyWindow::getMinesweeperHandle(){
    return minesweeperHandle;
}

void MyWindow::doSomething(int xPos, int yPos){
   
}