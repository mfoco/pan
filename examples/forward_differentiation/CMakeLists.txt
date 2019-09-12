cmake_minimum_required(VERSION 3.14)

add_executable(forward 
    main.cpp
)

target_link_libraries(forward PUBLIC pan matplotlib-cpp)
set_target_properties(forward PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 17
)
