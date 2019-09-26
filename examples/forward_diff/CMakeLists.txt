cmake_minimum_required(VERSION 3.14)

include(matplotlib)

add_executable(forward_diff_example
    df.hpp
    df.cpp
    main.cpp
)

target_link_libraries(forward_diff_example PUBLIC pan matplotlib)
set_target_properties(forward_diff_example PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 20
)
