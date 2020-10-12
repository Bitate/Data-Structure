#include <vector>
#include <algorithm>

using namespace std;

/**
 * O(n*elements_amount)
 */
int brute_force_max_sum(vector<int>& input_array, int elements_amount)
{
    int max_sum = 0;

    for(int i = 0; i < (input_array.size()-elements_amount+1); ++i)
    {
        int current_sum = 0;
        for(int j = 0; j < elements_amount; ++j)
        {
            current_sum += input_array[j+i];
        }

        max_sum = max(current_sum, max_sum);
    }

    return max_sum;
}

/**
 * O(n) 
 */
int window_sliding_max_sum(vector<int>& input_array, int elements_amount)
{
    int max_sum = 0;
    for(int i = 0; i < elements_amount; ++i)
        max_sum += input_array[i];

    // Compute sums of remaining windows by 
    // removing first element of previous 
    // window and adding last element of 
    // current window. 
    int window_sum = max_sum;
    for(int i = elements_amount; i < input_array.size(); ++i)
    {
        window_sum += input_array[i] - input_array[i-elements_amount];
        max_sum = max(max_sum, window_sum);
    }

    return max_sum;
}