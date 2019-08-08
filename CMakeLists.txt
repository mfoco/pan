cmake_minimum_required(VERSION 3.0.0)
project(pan VERSION 0.1.0)

add_subdirectory(pan)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
