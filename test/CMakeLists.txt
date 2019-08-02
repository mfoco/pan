cmake_minimum_required(VERSION 3.0.0)

include(CTest)
find_package(GTest)

enable_testing()

add_executable(test 
    main.cpp 
    arithmetic_tuple_test.cpp
    base_test.cpp
    imaginary_test.cpp
    imaginary_real_test.cpp
    imaginary_complex_test.cpp)

set_property(TARGET test PROPERTY CXX_STANDARD 17)

target_link_libraries(test gtest pthread)
