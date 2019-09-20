if(NOT TARGET matplotlib) 
    include(FetchContent)

    find_package (Python COMPONENTS Interpreter Development NumPy)

    FetchContent_Declare(matplotlib
        GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
        URL_HASH f4ad842e70cc56a38f3e4cd852968c7c1cecc9a7
    )

    FetchContent_GetProperties(matplotlib)
    if(NOT matplotlib_POPULATED)
        FetchContent_Populate(matplotlib)
    endif()

    add_library(matplotlib INTERFACE)
    target_sources(matplotlib INTERFACE $<BUILD_INTERFACE:${matplotlib_SOURCE_DIR}>)
    target_link_libraries(matplotlib INTERFACE $<BUILD_INTERFACE:${Python_LIBRARIES}>)
    target_include_directories(matplotlib INTERFACE $<BUILD_INTERFACE:${matplotlib_SOURCE_DIR}>)
    target_include_directories(matplotlib INTERFACE $<BUILD_INTERFACE:${Python_INCLUDE_DIRS}>)
    target_include_directories(matplotlib INTERFACE $<BUILD_INTERFACE:${Python_NumPy_INCLUDE_DIRS}>)

    message(${Python_LIBRARIES})
    message(${Python_INCLUDE_DIRS})
    message(${Python_NumPy_INCLUDE_DIRS})
endif()