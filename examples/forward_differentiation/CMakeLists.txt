cmake_minimum_required(VERSION 3.14)

include(matplotlib)

add_executable(forward 
    main.cpp
)

target_link_libraries(forward PUBLIC pan matplotlib)
set_target_properties(forward PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 20
)
