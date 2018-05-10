cmake_minimum_required(VERSION 2.8)
project(big_data_sort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

add_executable(big_data_sort main.cpp)

