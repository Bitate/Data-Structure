#include "../window_sliding.hpp"

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(window_sliding_tests, brute_force_test)
{
    vector<int> input = { 100, 200, 300, 400 };
    int elements_amount = 2;
    int output = 700;

    EXPECT_EQ( brute_force_max_sum(input, elements_amount), output );
}

TEST(window_sliding_tests, winodw_sliding_test)
{
    vector<int> input = { 100, 200, 300, 400 };
    int elements_amount = 2;
    int output = 700;

    EXPECT_EQ( window_sliding_max_sum(input, elements_amount), output );
}