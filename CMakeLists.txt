cmake_minimum_required(VERSION 3.8)
project(connected_components)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_library(kosaraju_lib kosaraju/kosaraju.cpp kosaraju/kosaraju.hpp)
add_library(dbscan_lib dbscan/dbscan.cpp dbscan/dbscan.hpp)

add_executable(kosaraju main_kosaraju.cpp)
add_executable(dbscan_point main_dbscan_point.cpp)
add_executable(dbscan_graph main_dbscan_dmatrix.cpp)

target_link_libraries(kosaraju PRIVATE kosaraju_lib)
target_link_libraries(dbscan_point PRIVATE dbscan_lib)
target_link_libraries(dbscan_graph PRIVATE dbscan_lib kosaraju_lib)