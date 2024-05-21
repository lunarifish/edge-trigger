cmake_minimum_required(VERSION 3.28)

project(edge_trigger CXX)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(edge_trigger)
add_subdirectory(test)