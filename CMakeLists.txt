cmake_minimum_required(VERSION 3.16)

project(MinesweeperSolver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(MyExecutable)

enable_testing()

add_subdirectory(googletest)
add_subdirectory(test)
add_subdirectory(src)
