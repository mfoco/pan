cmake_minimum_required(VERSION 3.14.0)
project(pan VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

option (WITH_PYTHON "enable targets using python bindings" OFF)

add_subdirectory(pan)
add_subdirectory(examples)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
