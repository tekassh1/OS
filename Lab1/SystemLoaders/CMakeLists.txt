cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(LinearRegressionl STATIC LinearRegression/LinearRegression.cpp)
target_include_directories(LinearRegressionl PUBLIC LinearRegression)

include(FetchContent)
FetchContent_Declare(
        ExternalSorter
        GIT_REPOSITORY https://github.com/tekassh1/TapeSort.git
        GIT_TAG main
        SOURCE_DIR SystemLoaders/ExternalSorter
)
FetchContent_MakeAvailable(ExternalSorter)