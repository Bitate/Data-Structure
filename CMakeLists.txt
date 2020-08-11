cmake_minimum_required(VERSION 3.8)

set(this Data-Structure)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "-g")

project(${this})

enable_testing()

add_subdirectory(googletest)
add_subdirectory(LockFree)
add_subdirectory(AVLTree)
add_subdirectory(Graph)
add_subdirectory(Sorting)
add_subdirectory(Queue)