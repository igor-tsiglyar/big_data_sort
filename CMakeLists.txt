cmake_minimum_required(VERSION 2.8)
project(big_data_sort)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.9")
        message(FATAL_ERROR "Insufficient gcc version")
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(big_data_sort main.cpp)

