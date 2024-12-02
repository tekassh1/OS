cmake_minimum_required(VERSION 3.10)

project(OS1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(OS1 ${SOURCES})

target_include_directories(OS1 PRIVATE include)

add_subdirectory(LinearRegression)

include(FetchContent)
FetchContent_Declare(
        ExternalSorter
        GIT_REPOSITORY https://github.com/tekassh1/TapeSort.git
        GIT_TAG main
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/ExternalSorter
)
FetchContent_MakeAvailable(ExternalSorter)