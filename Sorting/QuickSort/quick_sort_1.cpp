/**
 * Quick sort implemented with C++ template.
 * The pivot is the last element within unsorted array.
 */

#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>

template<typename T>
struct less
{
    bool operator()(T& v1, T& v2)     
    {
        return v1 < v2;
    }
};

template <typename E, typename C>
void quickSort(std::vector<E>& S, C& less) 
{
    if (S.size() <= 1) return;				        // already sorted
    quickSortStep(S, 0, S.size() - 1, less);		// call sort utility
}

// core quick sort function
template <typename E, typename C>
void quickSortStep(std::vector<E>& S, int a, int b, C& less) 
{
    if (a >= b) return;				// 0 or 1 left? done
    E pivot = S[b];					// select last as pivot
    int l = a; 						// index l scans the sequence from left to right 
    int r = b - 1;					// index r scans the sequence from right to left
    while (l <= r) 
    {
        while (l <= r && !less(pivot, S[l])) l++;		// scan right till larger
        while (r >= l && !less(S[r], pivot)) r--;		// scan left till smaller
        if (l < r) // both elements found
            std::swap(S[l], S[r]);
    }
    std::swap(S[l], S[b]);				// store pivot at l (left)

    // recur on left side
    quickSortStep(S, a, l - 1, less);	
    // recur on right side
    quickSortStep(S, l + 1, b, less);
}

int main()
{
    less<int> lessthan;
    
    std::vector<int> unsorted_ints = {1, 5, 4, 6, 141, 53, 6, 14341, 635 };

    std::cout << "Unsorted int array: " << std::endl;
    for (auto e : unsorted_ints)
        std::cout << e << " ";
    std::cout << std::endl;
    
    quickSort(unsorted_ints, lessthan);

    std::cout << "After performing quick-sort: " << std::endl;
    for (auto e : unsorted_ints)
        std::cout << e << " ";
    std::cout << std::endl;
    
}