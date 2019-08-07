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
    target_link_libraries(${TESTNAME} Catch2)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME}
        PROPERTIES 
            FOLDER tests
            CXX_STANDARD_REQUIRED ON
            CXX_STANDARD 17)
endmacro()

add_subdirectory(bases)
add_subdirectory(diff)
