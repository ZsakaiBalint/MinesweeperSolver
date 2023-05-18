# Minesweeper Solver

## About
This program solves the "Microsoft Minesweeper" game automatically. The project was written in C++ and runs on Windows.
The project uses cmake for building and ctest and googletest for testing.

## Project structure
.github/workflows/ : contains the yaml file that runs the CI/CD in github actions  
build/ : contains the built program and the test artifacts  
doc/ : contains my thesis, written in latex  
googletest/ : contains googletest  
src/ : contains all source files  
test/ : contains all test files  
tools/ : contains a build test that uses cmake  

## How to use the project
-> To build the project: run the PowerShell script, which is at: 'tools/build_script.ps1'  
it will build the latest version of the project  
the project and test artifacts are available in the 'build/' folder  
-> to run the program: run the exe file in the 'build/' folder

you can see the latest project version deployed at: http://zsakbalint.web.elte.hu/
