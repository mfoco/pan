cmake_minimum_required(VERSION 3.14)

include(matplotlib)
include(eigen)

add_executable(eigen_interaction 
    main.cpp
)

target_link_libraries(eigen_interaction PUBLIC pan matplotlib eigen)
set_target_properties(eigen_interaction PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 20
)
