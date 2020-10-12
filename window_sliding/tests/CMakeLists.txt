add_executable(window_sliding_solution_1_test
    ../window_sliding.hpp
    window_sliding_test.cpp
)
target_link_libraries(window_sliding_solution_1_test
    gtest_main
)