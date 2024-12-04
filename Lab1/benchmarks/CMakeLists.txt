cmake_minimum_required(VERSION 3.10)

project(Benchmarks VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        GoogleTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(GoogleTest)

FetchContent_Declare(
        GoogleBenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.9.1
)
FetchContent_MakeAvailable(GoogleBenchmark)

FetchContent_Declare(
        ExternalSorter
        GIT_REPOSITORY https://github.com/tekassh1/TapeSort.git
        GIT_TAG main
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/SystemLoaders/ExternalSorter
)
FetchContent_MakeAvailable(ExternalSorter)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(Benchmarks ${SOURCES})

add_dependencies(Benchmarks
    TapeSortl
)

target_link_libraries(Benchmarks PRIVATE benchmark TapeSortl)