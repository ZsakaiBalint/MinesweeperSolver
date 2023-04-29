#minimum cmake version
cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER $ENV{CC})
set(CMAKE_CXX_COMPILER $ENV{CXX})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#project name
project(MinesweeperSolver)

add_executable(MyExecutable)

add_subdirectory(src)
#comment

