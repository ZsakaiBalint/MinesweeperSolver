#minimum cmake version
cmake_minimum_required(VERSION 3.16)

#project name
project(MinesweeperSolver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(MyExecutable)

add_subdirectory(src)

