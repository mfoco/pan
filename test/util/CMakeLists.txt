cmake_minimum_required(VERSION 3.14)

package_add_test(util_test  
    main.cpp
    util_test.cpp
)

target_link_libraries(util_test PUBLIC pan)
set_target_properties(util_test PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 20
)
