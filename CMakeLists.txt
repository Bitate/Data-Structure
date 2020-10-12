cmake_minimum_required(VERSION 3.18)

set(this Data-Structure)

# For linux 
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(${this})

enable_testing()

add_subdirectory(googletest)
add_subdirectory(LockFree)
add_subdirectory(AVLTree)
add_subdirectory(Graph)
add_subdirectory(Sorting)
add_subdirectory(queue)
add_subdirectory(window_sliding)