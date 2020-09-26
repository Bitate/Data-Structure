#include "../queue.hpp"

#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(queue_tests, push_and_pop_test)
{
    container::queue<int> q;

    for(int i = 0; i < 99; ++i)
    {
        q.push(i);
    }
    cout << "After pushing, the size of queue is: " << q.size() << endl;

    for(int i = 0; i < 99; ++i)
    {
        q.pop();
    }
    cout << "After popping, the size of queue is: " << q.size() << endl;
}