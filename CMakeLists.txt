cmake_minimum_required(VERSION 3.10)
project(HeatEquation)

set(CMAKE_CXX_STANDARD 17)

add_executable(HeatEquation main.cpp vector.hpp matrix.hpp cg.hpp)

