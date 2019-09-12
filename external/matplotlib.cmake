include(FetchContent)

find_package (Python COMPONENTS Interpreter Development NumPy)

FetchContent_Declare(
  matplotlib
  GIT_REPOSITORY https://github.com/lava/matplotlib-cpp
)

FetchContent_MakeAvailable(matplotlib)

add_library(matplotlib-cpp INTERFACE)
target_sources(matplotlib-cpp INTERFACE $<BUILD_INTERFACE:${matplotlib_SOURCE_DIR}>)
target_link_libraries(matplotlib-cpp INTERFACE $<BUILD_INTERFACE:${Python_LIBRARIES}>)
target_include_directories(matplotlib-cpp INTERFACE $<BUILD_INTERFACE:${matplotlib_SOURCE_DIR}>)
target_include_directories(matplotlib-cpp INTERFACE $<BUILD_INTERFACE:${Python_INCLUDE_DIRS}>)
target_include_directories(matplotlib-cpp INTERFACE $<BUILD_INTERFACE:${Python_NumPy_INCLUDE_DIRS}>)

message(${Python_LIBRARIES})
message(${Python_INCLUDE_DIRS})
message(${Python_NumPy_INCLUDE_DIRS})
