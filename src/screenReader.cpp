#include "screenReader.h"

//This function reads the minefield by picture and produces a matrix which represents the minefield
//imageName: is the name of the image WITHOUT the path
//testMode: configures the folder of the images
std::vector<std::vector<Square>> ScreenReader::readMinefield(std::string imageName, double screenScaling,  bool testMode) {
    
    if(imageName == "") { throw std::runtime_error("no imageName was given"); }

    if (1.00 - screenScaling != 0 &&
        1.25 - screenScaling != 0 &&
        1.50 - screenScaling != 0 &&
        1.75 - screenScaling != 0) {
            throw std::runtime_error("UNKNOWN SCREEN SCALING..."); 
    }

    std::string imageFolder;
    
    if (testMode) {
        imageFolder = "../../images/testImages/";
    }
    else {
        imageFolder = "images/dependencyImages/";
    }

    std::string imageLocation = imageFolder + imageName;

    cv::Mat largeImage = cv::imread(imageLocation);
    if (largeImage.empty()) {
        throw std::runtime_error("Failed to load image: " + imageLocation);
    }

    //get the image dimensions
    int imageWidth = largeImage.cols;
    int imageHeight = largeImage.rows;

    std::vector<std::vector<Square>> matrix;

    if ( 
        (imageWidth == 128 && imageHeight == 128) || 
        (imageWidth == 160 && imageHeight == 160) ||  
        (imageWidth == 192 && imageHeight == 192) ||
        (imageWidth == 224 && imageHeight == 224) ) {

        matrix.assign(8, std::vector<Square>(8, ZERO));
    }
    else if ( 
        (imageWidth == 256 && imageHeight == 256) ||
        (imageWidth == 320 && imageHeight == 320) ||
        (imageWidth == 384 && imageHeight == 384) ||
        (imageWidth == 448 && imageHeight == 448) ) {
        
        matrix.assign(16, std::vector<Square>(16, ZERO));
    }
    else if (
        (imageWidth == 480 && imageHeight == 256) ||
        (imageWidth == 600 && imageHeight == 320) ||
        (imageWidth == 720 && imageHeight == 384) ||
        (imageWidth == 840 && imageHeight == 448)) {
 
        matrix.assign(16, std::vector<Square>(30, ZERO));
    }
    else {
        throw std::runtime_error("UNKNOWN MINEFIELD SIZE...");
    }
    


    if (testMode) {
        imageFolder = "../../images/dependencyImages/";
    }
    else {
        imageFolder = "images/dependencyImages/";
    }

    //set the decimals to two
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << screenScaling;
    std::string screenScalingSTR = stream.str();

    cv::Mat smallImageUNKNOWN   = cv::imread(imageFolder + "UNKNOWN" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageFLAGGED   = cv::imread(imageFolder + "FLAGGED" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageZERO      = cv::imread(imageFolder + "ZERO" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageONE       = cv::imread(imageFolder + "ONE" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageTWO       = cv::imread(imageFolder + "TWO" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageTHREE     = cv::imread(imageFolder + "THREE" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageFOUR      = cv::imread(imageFolder + "FOUR" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageFIVE      = cv::imread(imageFolder + "FIVE" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageSIX       = cv::imread(imageFolder + "SIX" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageSEVEN     = cv::imread(imageFolder + "SEVEN" + "_" + screenScalingSTR + ".png");
    cv::Mat smallImageEIGHT     = cv::imread(imageFolder + "EIGHT" + "_" + screenScalingSTR + ".png");

    if (smallImageUNKNOWN.empty() || smallImageFLAGGED.empty() || smallImageZERO.empty() ||
        smallImageONE.empty() || smallImageTWO.empty() || smallImageTHREE.empty() ||
        smallImageFOUR.empty() || smallImageFIVE.empty() || smallImageSIX.empty() ||
        smallImageSEVEN.empty() || smallImageEIGHT.empty()) {
        throw std::runtime_error("Failed to load one or more images");
    }

    
    cv::Mat resultUNKNOWN;
    cv::Mat resultFLAGGED;
    cv::Mat resultZERO;
    cv::Mat resultONE;
    cv::Mat resultTWO;
    cv::Mat resultTHREE;
    cv::Mat resultFOUR;
    cv::Mat resultFIVE;
    cv::Mat resultSIX;
    cv::Mat resultSEVEN;
    cv::Mat resultEIGHT;

    std::vector<cv::Point> locationsUNKNOWN;
    std::vector<cv::Point> locationsFLAGGED;
    std::vector<cv::Point> locationsZERO;
    std::vector<cv::Point> locationsONE;
    std::vector<cv::Point> locationsTWO;
    std::vector<cv::Point> locationsTHREE;
    std::vector<cv::Point> locationsFOUR;
    std::vector<cv::Point> locationsFIVE;
    std::vector<cv::Point> locationsSIX;
    std::vector<cv::Point> locationsSEVEN;
    std::vector<cv::Point> locationsEIGHT;

    double threshold = 0.8;

    cv::matchTemplate(largeImage, smallImageUNKNOWN, resultUNKNOWN, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultUNKNOWN, resultUNKNOWN, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultUNKNOWN, locationsUNKNOWN);

    cv::matchTemplate(largeImage, smallImageFLAGGED, resultFLAGGED, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultFLAGGED, resultFLAGGED, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultFLAGGED, locationsFLAGGED);

    cv::matchTemplate(largeImage, smallImageZERO, resultZERO, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultZERO, resultZERO, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultZERO, locationsZERO);

    cv::matchTemplate(largeImage, smallImageONE, resultONE, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultONE, resultONE, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultONE, locationsONE);

    cv::matchTemplate(largeImage, smallImageTWO, resultTWO, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultTWO, resultTWO, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultTWO, locationsTWO);

    cv::matchTemplate(largeImage, smallImageTHREE, resultTHREE, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultTHREE, resultTHREE, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultTHREE, locationsTHREE);

    cv::matchTemplate(largeImage, smallImageFOUR, resultFOUR, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultFOUR, resultFOUR, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultFOUR, locationsFOUR);

    cv::matchTemplate(largeImage, smallImageFIVE, resultFIVE, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultFIVE, resultFIVE, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultFIVE, locationsFIVE);

    cv::matchTemplate(largeImage, smallImageSIX, resultSIX, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultSIX, resultSIX, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultSIX, locationsSIX);

    cv::matchTemplate(largeImage, smallImageSEVEN, resultSEVEN, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultSEVEN, resultSEVEN, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultSEVEN, locationsSEVEN);

    cv::matchTemplate(largeImage, smallImageEIGHT, resultEIGHT, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultEIGHT, resultEIGHT, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultEIGHT, locationsEIGHT);


    std::string printResult = "";
    int squareSizeInPixels = 16;

    for (const auto& location : locationsUNKNOWN) {
        int row = static_cast<int>( location.y / (squareSizeInPixels * screenScaling) );
        int col = static_cast<int>( location.x / (squareSizeInPixels * screenScaling) );
        matrix[row][col] = UNKNOWN;
    }
  
    for (const auto& location : locationsFLAGGED) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = FLAGGED;
    }
    //don't template match for zero, it is the default for every square
    /*
    for (const auto& location : locationsZERO) {
        int row = static_cast<int>( location.y / (squareSizeInPixels * screenScaling) );
        int col = static_cast<int>( location.x / (squareSizeInPixels * screenScaling) );
        matrix[row][col] = ZERO;
    }
    */
    for (const auto& location : locationsONE) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = ONE;
    }
    for (const auto& location : locationsTWO) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = TWO;
    }
    for (const auto& location : locationsTHREE) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = THREE;
    }
    for (const auto& location : locationsFOUR) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = FOUR;
    }
    for (const auto& location : locationsFIVE) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = FIVE;
    }
    for (const auto& location : locationsSIX) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = SIX;
    }
    for (const auto& location : locationsSEVEN) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = SEVEN;
    }
    for (const auto& location : locationsEIGHT) {
        int row = static_cast<int>(location.y / (squareSizeInPixels * screenScaling));
        int col = static_cast<int>(location.x / (squareSizeInPixels * screenScaling));
        matrix[row][col] = EIGHT;
    }


    //There is a bug where sometimes a square is falsely identified as ZERO instead of UNKNOWN.
    //A rule exists in minesweeper that states:  
    //"a ZERO square (a square with no adjacent mines) reveals all adjacent squares automatically when clicked."
    //So in any minesweeper configuration, a ZERO square with all of it's adjacent squares being UNKNOWN shouldn't exist
    //we solve this by assigning the UNKNOWN value to all of these ZERO squares
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            if (matrix[i][j] == ZERO) {
                std::vector<Square> adjacent = getAdjacentElements(matrix, i, j);
                bool allUnknown = true;
                for (const auto& elem : adjacent) {
                    if (elem != UNKNOWN) {
                        allUnknown = false;
                        break;
                    }
                }
                if (allUnknown) {
                    matrix[i][j] = UNKNOWN;
                }
            }
        }
    }




    return matrix;
}

void ScreenReader::screenshotIsAlive(double screenScaling) {

    if (1.00 - screenScaling != 0 &&
        1.25 - screenScaling != 0 &&
        1.50 - screenScaling != 0 &&
        1.75 - screenScaling != 0) {
        throw std::runtime_error("UNKNOWN SCREEN SCALING...");
    }

    RECT minesweeperWindow;
    GetWindowRect(minesweeperHandle, &minesweeperWindow);

    //int screenshotWidth = minesweeperWindow.right - minesweeperWindow.left;
    int screenshotWidth = static_cast<int>((minesweeperWindow.right - minesweeperWindow.left) * screenScaling);
    int screenshotHeight = static_cast<int>(100 * screenScaling);

    //int screenshotX = static_cast<int>((minesweeperWindow.left + 15) * screenScaling);
    //int screenshotY = static_cast<int>((minesweeperWindow.top + 101) * screenScaling);

    int screenshotX = static_cast<int>(minesweeperWindow.left * screenScaling);
    int screenshotY = static_cast<int>(minesweeperWindow.top * screenScaling);

    // Create a device context for the entire screen
    HDC hScreenDC = GetDC(NULL);

    // Create a compatible device context
    HDC hMemDC = CreateCompatibleDC(hScreenDC);

    // Create a compatible bitmap
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenshotWidth, screenshotHeight);

    // Select the bitmap into the compatible device context
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // Copy the screen contents within the ROI into the compatible device context
    BitBlt(hMemDC, 0, 0, screenshotWidth, screenshotHeight, hScreenDC, screenshotX, screenshotY, SRCCOPY);

    // Create an OpenCV Mat object from the compatible bitmap
    cv::Mat screenshot(screenshotHeight, screenshotWidth, CV_8UC4);
    GetBitmapBits(hBitmap, screenshot.total() * screenshot.elemSize(), screenshot.data);

    // Release the resources
    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemDC);
    ReleaseDC(NULL, hScreenDC);

    // Save the screenshot as an image file
    std::string outputfilePath = "images/dependencyImages/isalive_screenshot.png";
    cv::imwrite(outputfilePath, screenshot);
}

void ScreenReader::screenshotMinefield(double screenScaling) {

    if (1.00 - screenScaling != 0 &&
        1.25 - screenScaling != 0 &&
        1.50 - screenScaling != 0 &&
        1.75 - screenScaling != 0) {
        throw std::runtime_error("UNKNOWN SCREEN SCALING...");
    }

    RECT minesweeperWindow;
    GetWindowRect(minesweeperHandle, &minesweeperWindow);


    int screenshotX = static_cast<int>( (minesweeperWindow.left + 15) * screenScaling );
    int screenshotY = static_cast<int>( (minesweeperWindow.top + 101) * screenScaling );

    int screenshotWidth = static_cast<int>(difficulty.getWidth() * 16 * screenScaling);
    int screenshotHeight = static_cast<int>(difficulty.getHeight() * 16 * screenScaling);
   

    // Create a device context for the entire screen
    HDC hScreenDC = GetDC(NULL);

    // Create a compatible device context
    HDC hMemDC = CreateCompatibleDC(hScreenDC);

    // Create a compatible bitmap
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenshotWidth, screenshotHeight);

    // Select the bitmap into the compatible device context
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // Copy the screen contents within the ROI into the compatible device context
    BitBlt(hMemDC, 0, 0, screenshotWidth, screenshotHeight, hScreenDC, screenshotX, screenshotY, SRCCOPY);

    // Create an OpenCV Mat object from the compatible bitmap
    cv::Mat screenshot(screenshotHeight, screenshotWidth, CV_8UC4);
    GetBitmapBits(hBitmap, screenshot.total() * screenshot.elemSize(), screenshot.data);

    // Release the resources
    SelectObject(hMemDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemDC);
    ReleaseDC(NULL, hScreenDC);

    // Save the screenshot as an image file
    std::string outputfilePath = "images/dependencyImages/minesweeper_screenshot.png";
    cv::imwrite(outputfilePath, screenshot);
}

bool ScreenReader::readIsAlive(std::string imageName, double screenScaling, bool testMode) {
    //we have to template match 2 images:
    //the first image occurs when the user doesn't give any input to the game
    //the second image occurs while the user clicks on a square

    if (1.00 - screenScaling != 0 &&
        1.25 - screenScaling != 0 &&
        1.50 - screenScaling != 0 &&
        1.75 - screenScaling != 0) {
        throw std::runtime_error("UNKNOWN SCREEN SCALING...");
    }

    if (imageName == "") { throw std::runtime_error("no imageName was given"); }

    std::string imageFolder;

    if (testMode) {
        imageFolder = "../../images/testImages/";
    }
    else {
        imageFolder = "images/dependencyImages/";
    }


    cv::Mat largerImage = cv::imread(imageFolder + imageName);
    if (largerImage.empty()) {
        throw std::runtime_error("Failed to load image: " + imageFolder);
    }


    if (testMode) {
        imageFolder = "../../images/dependencyImages/";
    }
    else {
        imageFolder = "images/dependencyImages/";
    }


    //set the decimals to two
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << screenScaling;
    std::string screenScalingSTR = stream.str();

    cv::Mat smallerImageSMILEY = cv::imread(imageFolder + "SMILEY" + "_" + screenScalingSTR + ".png");
    cv::Mat smallerImageSMILEY_CLICK = cv::imread(imageFolder + "SMILEY_CLICK" + "_" + screenScalingSTR + ".png");

    // Ensure all images are loaded successfully
    if (largerImage.empty() || smallerImageSMILEY.empty() || smallerImageSMILEY_CLICK.empty() )
    {
        std::cout << "Failed to load one or more images" << std::endl;
        return -1;
    }

    // Perform template matching
    cv::Mat resultSMILEY;
    cv::Mat resultSMILEY_CLICK;

    std::vector<cv::Point> locationsSMILEY;
    std::vector<cv::Point> locationsSMILEY_CLICK;

    double threshold = 0.91;

    cv::matchTemplate(largerImage, smallerImageSMILEY, resultSMILEY, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultSMILEY, resultSMILEY, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultSMILEY, locationsSMILEY);

    cv::matchTemplate(largerImage, smallerImageSMILEY_CLICK, resultSMILEY_CLICK, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultSMILEY_CLICK, resultSMILEY_CLICK, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultSMILEY_CLICK, locationsSMILEY_CLICK);

    return ( (locationsSMILEY.size() != 0) || (locationsSMILEY_CLICK.size() != 0));
}

bool ScreenReader::readIsWon(std::string imageName, double screenScaling, bool testMode) {
    //we have to template match one image, the smiley with the sunglasses

    if (1.00 - screenScaling != 0 &&
        1.25 - screenScaling != 0 &&
        1.50 - screenScaling != 0 &&
        1.75 - screenScaling != 0) {
        throw std::runtime_error("UNKNOWN SCREEN SCALING...");
    }

    if (imageName == "") { throw std::runtime_error("No imageName was given"); }
    std::string imageFolder;

    if (testMode) {
        imageFolder = "../../images/testImages/";
    }
    else {
        imageFolder = "images/dependencyImages/";
    }

    std::string imageLocation = imageFolder + imageName;
    cv::Mat largerImage = cv::imread(imageLocation);


    if (testMode) {
        imageFolder = "../../images/dependencyImages/";
    }
    else {
        imageFolder = "images/dependencyImages/";
    }


    //set the decimals to two
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << screenScaling;
    std::string screenScalingSTR = stream.str();

    cv::Mat smallerImage = cv::imread(imageFolder + "SMILEY_WON" + "_" + screenScalingSTR + ".png");


    // Ensure all images are loaded successfully
    if (largerImage.empty() || smallerImage.empty())
    {
        std::cout << "Failed to load one or more images" << std::endl;
        return -1;
    }

    // Perform template matching
    cv::Mat resultWON;

    std::vector<cv::Point> locationsWON;

    double threshold = 0.8;

    cv::matchTemplate(largerImage, smallerImage, resultWON, cv::TM_CCOEFF_NORMED);
    cv::threshold(resultWON, resultWON, threshold, 1.0, cv::THRESH_TOZERO);
    cv::findNonZero(resultWON, locationsWON);

    return ( locationsWON.size() != 0 );
}

std::vector<std::pair<int, int>> ScreenReader::getMinefieldDifference(std::vector<std::vector<Square>> prevMinefield, std::vector<std::vector<Square>> currentMinefield) {

    std::vector<std::pair<int, int>> differences;

    for (unsigned i = 0; i < prevMinefield.size(); ++i) {
        for (unsigned j = 0; j < prevMinefield[i].size(); ++j) {

            if (prevMinefield[i][j] != currentMinefield[i][j]) {
                differences.push_back({ i,j });
            }
        }
    }
    return differences;
}

ScreenReader::ScreenReader(Difficulty difficulty,HWND minesweeperHandle): difficulty(difficulty), minesweeperHandle(minesweeperHandle) {
    int rows = difficulty.getHeight();
    int cols = difficulty.getWidth();
    this->previousMinefield =  std::vector<std::vector<Square>> (rows, std::vector<Square>(cols, UNKNOWN));
}

void ScreenReader::setPreviousMinefield(std::vector<std::vector<Square>> minefield) {
    this->previousMinefield = minefield;
}

std::vector<std::vector<Square>> ScreenReader::getPreviousMinefield() {
    return this->previousMinefield;
}

bool ScreenReader::isMinefieldInitial(std::string imageName, double screenScaling, bool testMode) {

    std::vector<std::vector<Square>> matrix = readMinefield(imageName,screenScaling, testMode);
    for (unsigned i = 0; i < matrix.size(); ++i) {
        for (unsigned j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != UNKNOWN) { return false; }
        }
    }
    return true;
}

double ScreenReader::getScreenScaling() {

    auto activeWindow = GetActiveWindow();
    HMONITOR monitor = MonitorFromWindow(activeWindow, MONITOR_DEFAULTTONEAREST);

    // Get the logical width and height of the monitor
    MONITORINFOEX monitorInfoEx;
    monitorInfoEx.cbSize = sizeof(monitorInfoEx);
    GetMonitorInfo(monitor, &monitorInfoEx);
    auto cxLogical = monitorInfoEx.rcMonitor.right - monitorInfoEx.rcMonitor.left;
    auto cyLogical = monitorInfoEx.rcMonitor.bottom - monitorInfoEx.rcMonitor.top;

    // Get the physical width and height of the monitor
    DEVMODE devMode;
    devMode.dmSize = sizeof(devMode);
    devMode.dmDriverExtra = 0;
    EnumDisplaySettings(monitorInfoEx.szDevice, ENUM_CURRENT_SETTINGS, &devMode);
    auto cxPhysical = devMode.dmPelsWidth;
    auto cyPhysical = devMode.dmPelsHeight;

    // Calculate the scaling factor
    auto horizontalScale = ((double)cxPhysical / (double)cxLogical);
    auto verticalScale = ((double)cyPhysical / (double)cyLogical);

    // Round to 2 decimal places
    horizontalScale = std::round(horizontalScale * 100.0) / 100.0;

    return horizontalScale;
}





bool ScreenReader::isValidIndex(int i, int j, int numRows, int numCols) {
    return i >= 0 && i < numRows && j >= 0 && j < numCols;
}

std::vector<Square> ScreenReader::getAdjacentElements(const std::vector<std::vector<Square>>& matrix, int row, int col) {
    std::vector<Square> adjacentElements;

    int numRows = matrix.size();
    int numCols = matrix[0].size();

    // Iterate over adjacent elements
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            if (isValidIndex(i, j, numRows, numCols) && !(i == row && j == col)) {
                adjacentElements.push_back(matrix[i][j]);
            }
        }
    }

    return adjacentElements;
}