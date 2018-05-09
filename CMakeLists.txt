cmake_minimum_required(VERSION 3.5)
project(big_data_sort)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(big_data_sort main.cpp)
