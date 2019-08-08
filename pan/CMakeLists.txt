
cmake_minimum_required(VERSION 3.14)

set(header_files
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/bases/arithmetic_tuple.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/bases/base.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/bases/imaginary.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/bases/dual.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/expr/diff.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/expr/expr_printer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/expr/expr.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/expr/opt.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/integer/integer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/integer/range.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/pan/integer/tag.hpp
)

add_library(pan INTERFACE)
target_sources(pan INTERFACE "$<BUILD_INTERFACE:${header_files}>")
target_include_directories(pan INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_include_directories(pan SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/>)
