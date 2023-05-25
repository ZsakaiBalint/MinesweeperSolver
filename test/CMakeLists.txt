cmake_minimum_required(VERSION 3.16)

add_library(mylibrary ../src/equation.cpp ../src/window.cpp)

add_executable(windowTest)
target_sources(windowTest PRIVATE windowTest.cpp )


add_executable(equationTest)
target_sources(equationTest PRIVATE equationTest.cpp )

target_link_libraries(windowTest PUBLIC 
    gtest_main
    mylibrary
)

target_link_libraries(equationTest PUBLIC 
    gtest_main
    mylibrary
)

add_test(
    NAME testname1
    COMMAND windowTest 
)

add_test(
    NAME testname2
    COMMAND equationTest
)