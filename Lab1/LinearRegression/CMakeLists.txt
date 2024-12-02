cmake_minimum_required(VERSION 3.10)

project(LinearRegression VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(LinearRegression ${SOURCES})