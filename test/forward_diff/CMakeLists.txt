cmake_minimum_required(VERSION 3.14)

package_add_test(forward_diff_test  
    main.cpp
    forward_diff_test.cpp
)

target_link_libraries(forward_diff_test PUBLIC pan)
set_target_properties(forward_diff_test PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 17
)
