cmake_minimum_required(VERSION 3.16)

add_executable(Tests)
target_sources(Tests PRIVATE windowTest.cpp)

target_link_libraries(Tests PUBLIC 
    gtest_main
)

add_test(
    NAME testname
    COMMAND Tests
)