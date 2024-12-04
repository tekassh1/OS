cmake_minimum_required(VERSION 3.10)

project(OS1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(OS1 ${SOURCES})

target_include_directories(OS1 PRIVATE include)

#add_subdirectory(SystemLoaders/LinearRegression)
add_subdirectory(benchmarks)

add_dependencies(OS1
    Benchmarks
)