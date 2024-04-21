#include "window.h"
#include "screenReader.h"

HHOOK g_hHook = NULL;

Window::~Window()
{
    if (hwnd) 
        DestroyWindow(hwnd);
}

Window::Window() : buttonHandler(), guiData()
{
    //load the icon
    std::wstring iconPath = L"images/dependencyImages/icon.ico";
    HICON windowIcon = (HICON)LoadImage(GetModuleHandle(NULL), iconPath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    if (windowIcon == NULL) {  }

    // Register window class
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"WindowClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = windowIcon;
    if (!RegisterClassEx(&wc)) {

    }

    //create the window (1100,650)
    this->hwnd = CreateWindowEx(0, wc.lpszClassName, L"Minesweeper X solver", WS_OVERLAPPEDWINDOW,
        0, 0, 1100, 650, NULL, NULL, wc.hInstance, NULL);
    if (this->hwnd) {};
    

    //get the handle to the minesweeper window
    bool onlyOneMinesweeper = checkMinesweeperWindows();
    while (!onlyOneMinesweeper) {
        const int result = MessageBoxA(hwnd, "Open exactly one MinesweeperX window.", "ERROR", MB_OKCANCEL);
        switch (result) {
            case IDOK:
                break;
            case IDCANCEL:
                PostQuitMessage(0);
                break;
        }
        onlyOneMinesweeper = checkMinesweeperWindows();
    }

    //move the minesweeper window to a desired location
    SetWindowPos(hwndMinesweeper, HWND_TOP, 15, 40, 0, 0, SWP_NOSIZE);
    SetWindowPos(hwndMinesweeper, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    //this is needed so we can access the Window class's functions in the callback
    SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    //initialize gdiplus
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    //create the 'log' component
    hwndLog = CreateWindowExA(
        0, "EDIT", nullptr,
        WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY,
        530, 350, 380, 200,
        hwnd, nullptr, GetModuleHandle(NULL), nullptr);

    //create the buttons
    hwndButton1 = CreateWindowW(
        L"BUTTON",                     
        L"STEP",                   	   
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        50, 400, 100, 30,              
        hwnd,                          
        (HMENU)1,                     
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL                           
    );

    hwndButton2 = CreateWindowW(
        L"BUTTON",                     
        L"EXECUTE",                   
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        200, 400, 100, 30,            
        hwnd,                       
        (HMENU)2,                      
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL                           
    );

    hwndButton3 = CreateWindowW(
        L"BUTTON",               
        L"TEST",                 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
        350, 400, 100, 30,             
        hwnd,                         
        (HMENU)3,                    
        (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
        NULL                           
    );

    //create the draw area
    hwndDraw = CreateWindowW(
        L"STATIC",
        nullptr,
        WS_CHILD | WS_VISIBLE | SS_OWNERDRAW,
        530, 70, 481, 257,
        hwnd, nullptr, GetModuleHandle(nullptr), nullptr
    );


    buttonHandler.setMinesweeperHandle(hwndMinesweeper);
    Difficulty d = getDifficulty();
    buttonHandler.setDifficulty(d);

    ShowWindow(hwnd, SW_SHOW);

    UpdateWindow(hwnd);

}

void Window::RunMessageLoop()
{
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

Difficulty Window::getDifficulty() {

    RECT windowRect;
    GetWindowRect(hwndMinesweeper, &windowRect);

    int windowWidth = windowRect.right - windowRect.left;
    int windowHeight = windowRect.bottom - windowRect.top;

    double screenMagnification = this->buttonHandler.getScreenScaling();
    const double epsilon = 1;

    if (windowWidth == 158 && windowHeight == 244) {
        Beginner b;
        return b;
    }
    else if (windowWidth == 286 && windowHeight == 372) {
        Intermediate i;
        return i;
    }
    else if (windowWidth == 510 && windowHeight == 372) {
        Expert e;
        return e;
    }

    else {
        throw std::runtime_error("unknown map difficulty");
    }

}

RECT Window::getMinesweeperRect() {
    RECT minesweeperRect = {};
    GetWindowRect(hwndMinesweeper, &minesweeperRect);
    return minesweeperRect;
}

#define TIMER_MOVE_DELAY 1

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    PAINTSTRUCT ps;
    HDC hdc;
    Gdiplus::Graphics* gf;

    static bool timerRunning = false;

    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_COMMAND:
            if (window == nullptr)
                break;

            window->handleButtonClick(LOWORD(wParam));
            return 0;
            
        case WM_PAINT:

            hdc = BeginPaint(hwnd, &ps);
            gf = new Gdiplus::Graphics(hdc);
            window->paintBackground(*gf, ps);
            EndPaint(hwnd, &ps);


            hdc = BeginPaint(window->getDrawArea(), &ps);
            gf = new Gdiplus::Graphics(hdc);
            window->paintMatrix(*gf);
            delete gf; 
            gf = nullptr; 
            EndPaint(window->getDrawArea(), &ps);
            return 0;

        case WM_ERASEBKGND:
            // Return TRUE to indicate that background was erased to prevent flickering
            return TRUE;

        case WM_MOVE:
            // Reset the timer every time the window is moved
            SetTimer(hwnd, TIMER_MOVE_DELAY, 250, nullptr); // Set a 1-second timer
            timerRunning = true;
            break;

        case WM_TIMER:
            // Handle the timer event (timer has expired)
            if (wParam == TIMER_MOVE_DELAY) {
                // Call the moveMinesweeperWindow function here
                window->moveMinesweeperWindow();
                timerRunning = false; // Reset the flag
            }
            break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void Window::logMessage(const std::string& message) {
    std::string appendedMessage = message;
    appendedMessage.append("\n");

    int length = GetWindowTextLengthA(hwndLog);
    SendMessageA(hwndLog, EM_SETSEL, length, length);
    SendMessageA(hwndLog, EM_REPLACESEL, FALSE, reinterpret_cast<LPARAM>(appendedMessage.c_str()));
    SendMessageA(hwndLog, EM_SCROLLCARET, 0, 0);
}

void Window::paintMatrix(Gdiplus::Graphics& gf) {

    //Difficulty d = getDifficulty();

    //int rows = d.getHeight();
    //int cols = d.getWidth();
    std::vector<std::vector<PaintableSquare>> paintableMatrix = buttonHandler.getPaintableMatrix();
    //std::vector<std::vector<PaintableSquare>> paintableMatrix = std::vector<std::vector<PaintableSquare>>(rows, std::vector<PaintableSquare>(cols, PaintableSquare()));

    Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 0));
    int rectSide = 16;

    for (int row = 0; row < paintableMatrix.size(); ++row) {
        for (int col = 0; col < paintableMatrix[row].size(); ++col) {

            PaintableSquare ps = paintableMatrix[row][col];
            Gdiplus::Color brushColor = Gdiplus::Color(ps.alpha, ps.red, ps.green, ps.blue);
            Gdiplus::SolidBrush brush(brushColor);
            gf.FillRectangle(&brush, col * rectSide, row * rectSide, rectSide, rectSide);
            gf.DrawRectangle(&pen, col * rectSide, row * rectSide, rectSide, rectSide);
        }
    }

}

void Window::paintBackground(Gdiplus::Graphics& gf, PAINTSTRUCT& ps) {

    // Set the background color to gray
    Gdiplus::SolidBrush brush(Gdiplus::Color(128, 128, 128));
    int width = ps.rcPaint.right - ps.rcPaint.left;
    int height = ps.rcPaint.bottom - ps.rcPaint.top;
    int x = ps.rcPaint.left;
    int y = ps.rcPaint.top;

    //paint the entire window's area
    gf.FillRectangle(&brush, x, y, width, height);
}

int Window::CountWindowsWithClassName(const char* className) {
    int count = 0;
    HWND window = NULL;

    while ((window = FindWindowExA(NULL, window, className, NULL)) != NULL) {
        ++count;
    }

    return count;
}

bool Window::checkMinesweeperWindows() {
    hwndMinesweeper = FindWindowA(NULL, "Minesweeper X");
    if (hwndMinesweeper == NULL) { return false; }
    char className[256];
    GetClassNameA(hwndMinesweeper, className, sizeof(className));
    if (CountWindowsWithClassName(className) != 1) { return false; }
    return true;
}

void Window::handleButtonClick(int buttonID) {

    std::string newMessage;
    RECT minesw;
    UINT dpi;

    bool isClosed = checkMinesweeperClosed();
    if (isClosed) { return; }

    bool minimised = checkMinesweeperMinimised();
    if (minimised) { return; }

    bool illegalLocation = checkMinesweeperIllegalLocation();
    if (illegalLocation) { return; }

    switch (buttonID) {
    case 1: // Button 1 clicked
        logMessage("step clicked");
        buttonHandler.setDifficulty(this->getDifficulty());
        buttonHandler.step();
        InvalidateRect(hwnd, nullptr, TRUE);
        logMessage(buttonHandler.getLastLogMessage());
        break;
    case 2: // Button 2 clicked
        logMessage("execute clicked");
        buttonHandler.setDifficulty(this->getDifficulty());
        buttonHandler.execute();
        break;
    case 3: // Button 3 clicked
        logMessage("test clicked");
        buttonHandler.setDifficulty(this->getDifficulty());
        buttonHandler.test();

        //DEBUG
        logMessage(buttonHandler.getLastLogMessage());
        logMessage(buttonHandler.getLastLogMessage());

        logMessage("testing finished successfully");
        break;
    }

}

HWND Window::getDrawArea() {
    return hwndDraw;
}

void Window::moveMinesweeperWindow() {

    //obtain the current position of this window
    RECT applicationWindow;
    GetWindowRect(hwnd, &applicationWindow);

    //adjust the minesweeper window's position according to it
    int newX = applicationWindow.left + 15;
    int newY = applicationWindow.top + 40;
    SetWindowPos(hwndMinesweeper, NULL, newX, newY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

bool Window::IsMinesweeperPartiallyInViewport() {
    RECT windowRect;
    GetWindowRect(hwndMinesweeper, &windowRect);

    int minesweeperWidth = windowRect.right - windowRect.left;
    int minesweeperHeight = windowRect.top - windowRect.bottom;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    return windowRect.left < 0 ||
        windowRect.top < 0 ||
        screenHeight < windowRect.bottom ||
        screenWidth < windowRect.right;
}

bool Window::checkMinesweeperIllegalLocation() {
  
    //get the handle to the minesweeper window
    bool minesweeperPartiallyInViewPort = IsMinesweeperPartiallyInViewport();
    if (minesweeperPartiallyInViewPort) {
        const int result = MessageBoxA(hwnd, "Illegal MinesweeperX window location. Would you like to move it to the center?", "ERROR", MB_OKCANCEL);
        switch (result) {
        case IDOK:
            SetWindowPos(hwnd, NULL, 100, 100, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            return true;
            break;
        case IDCANCEL:
            PostQuitMessage(0);
            return false;
            break;
        }
    }
    return false;
}

bool Window::checkMinesweeperMinimised() {

    bool minesweeperMinimised = IsIconic(hwndMinesweeper) != 0;
    if (minesweeperMinimised) {
        const int result = MessageBoxA(hwnd, "The MinesweeperX window is minimised. Would you like to restore it?", "ERROR", MB_OKCANCEL);
        switch (result) {
        case IDOK:
            ShowWindow(hwndMinesweeper, SW_RESTORE);
            return true;
            break;
        case IDCANCEL:
            PostQuitMessage(0);
            return false;
            break;
        }
    }

    return false;
}

bool Window::checkMinesweeperClosed() {

    bool minesweeperClosed = !IsWindow(hwndMinesweeper);
    if (minesweeperClosed) {
        PostQuitMessage(0);
        return true;
    }
    else {
        return false;
    }
}