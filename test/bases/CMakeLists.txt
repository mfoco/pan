cmake_minimum_required(VERSION 3.14)

package_add_test(bases_test 
    main.cpp 
    #arithmetic_tuple_test.cpp
    base_test.cpp
    imaginary_test.cpp
    imaginary_real_test.cpp
    imaginary_complex_test.cpp
)
target_link_libraries(bases_test PUBLIC pan)
set_target_properties(bases_test PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_STANDARD 20
)
