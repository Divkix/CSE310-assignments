cmake_minimum_required(VERSION 3.28)
project(dijkstra_algo)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(dijkstra_algo
        src/chauhan_TestGraph.cpp
        src/MatrixGraph_chauhan.cpp
        src/MatrixGraph_chauhan.h
        src/minmaxheap_chauhan.hpp
        src/Queue_chauhan.hpp)
