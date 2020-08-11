#include "queue.hpp"

#include <iostream>

using namespace std;

int main()
{
    bitate::queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    cout << "Size of queue is: " << queue.size() << endl;
    
    queue.pop();
    queue.pop();
    queue.pop();
    cout << "Size of queue is: " << queue.size() << endl;
    return 0;
}