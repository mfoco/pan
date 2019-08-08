cmake_minimum_required(VERSION 3.14)

package_add_test(expr_test  
    main.cpp
    diff_test.cpp
    expr_test.cpp
    expr_printer_test.cpp
    opt_test.cpp
)
target_link_libraries(expr_test PUBLIC pan)
set_target_properties(expr_test PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 17
)
