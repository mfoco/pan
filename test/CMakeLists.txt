
include(catch2)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} PUBLIC catch2)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
endmacro()

add_subdirectory(bases)
add_subdirectory(expr)
add_subdirectory(forward_diff)
add_subdirectory(util)
