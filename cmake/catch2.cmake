if(NOT TARGET catch2)
    cmake_minimum_required(VERSION 3.14)

    include(FetchContent)

    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.9.2
    )

    FetchContent_GetProperties(catch2)
    if(NOT catch2_POPULATED)
        FetchContent_Populate(catch2)
    endif()

    add_library(catch2 INTERFACE)
    target_include_directories(catch2 INTERFACE $<BUILD_INTERFACE:${catch2_SOURCE_DIR}>/single_include/)
endif()