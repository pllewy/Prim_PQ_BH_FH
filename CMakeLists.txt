cmake_minimum_required(VERSION 3.27)
project(Prim_PQ_BH_FH)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Prim_PQ_BH_FH main.cpp)
