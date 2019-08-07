cmake_minimum_required(VERSION 3.14)

package_add_test(diff_test  main.cpp
                            diff_test.cpp
                            expr_test.cpp
                            expr_printer_test.cpp
                            opt_test.cpp)
