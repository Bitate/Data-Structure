#include <vector>
#include <iostream>

template<typename comparable>
void insertion_sort( std::vector<comparable>& sequence)
{
    for(int p = 1; p < sequence.size(); ++p)
    {
        // tmp is current element
        comparable tmp = std::move( sequence[ p ] );

        int j = 0;
        for(j = p; j > 0 && tmp < sequence[ j - 1 ]; --j)
            // move all elements to right by 1
            // to make root for current
            sequence[ j ] = std::move( sequence[ j - 1 ] );
        // correct position for current
        sequence[ j ] = std::move( tmp );
    }
}

int main()
{
    std::vector<int> test_sequence = { 4,1,5,6,2,7,3,9,8 };
    insertion_sort<int>(test_sequence);
    for(int i = 0; i < test_sequence.size(); ++i)
    {
        std::cout << test_sequence[i] << ' ';
    }
}