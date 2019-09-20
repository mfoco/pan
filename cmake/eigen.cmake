
if(NOT TARGET eigen)
    include(FetchContent)

    FetchContent_Declare(eigen
        GIT_REPOSITORY https://github.com/eigenteam/eigen-git-mirror.git
        GIT_TAG 3.3.7
    )

    FetchContent_GetProperties(eigen)
    if(NOT eigen_POPULATED)
        FetchContent_Populate(eigen)
    endif()

    add_library(eigen INTERFACE)
    target_include_directories(eigen INTERFACE $<BUILD_INTERFACE:${eigen_SOURCE_DIR}>)
endif()