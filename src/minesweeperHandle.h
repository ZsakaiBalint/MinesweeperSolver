#pragma once

#include <Windows.h>

class MinesweeperHandle {

  public:
    MinesweeperHandle();
    MinesweeperHandle(const MinesweeperHandle&) = delete; 
    MinesweeperHandle& operator = (const MinesweeperHandle&) = delete;
    ~MinesweeperHandle();

    bool isMinesweeperOpen();
    RECT getMinesweeperRect();
    
  private:
    HWND minesweeperWindowHandle;
};