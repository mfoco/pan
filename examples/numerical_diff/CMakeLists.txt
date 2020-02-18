cmake_minimum_required(VERSION 3.14)

add_executable(numerical_diff_example
    main.cpp
)

target_link_libraries(numerical_diff_example PUBLIC pan)
set_target_properties(numerical_diff_example PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 20
)
