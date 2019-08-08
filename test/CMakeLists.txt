cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.9.1
)

FetchContent_MakeAvailable(catch2)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} PUBLIC Catch2)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
endmacro()

add_subdirectory(bases)
add_subdirectory(expr)
