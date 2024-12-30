cmake_minimum_required(VERSION 3.10)

project(OS1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(OS1 ${SOURCES})

target_include_directories(OS1 PRIVATE include)

add_subdirectory(SystemLoaders)
add_subdirectory(benchmarks)

add_dependencies(OS1
    Benchmarks
)