project(Queue CXX)

# For header only library
add_library(queue_detail INTERFACE)
target_sources(queue_detail INTERFACE queue.hpp)

add_subdirectory(tests)