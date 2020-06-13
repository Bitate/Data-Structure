//
// QuickSort
// Sorts elements into ascending/increasing order.
// pivot move from rightmost to leftmost at the end.
// 

#include <vector>
#include <functional>
#include <iostream>
#include <algorithm>

template<typename T>
struct less
{
    // Don't omit const keyword, click below link for why
    // https://stackoverflow.com/questions/19816139/expression-having-type-const-comparevptrs-would-lose-some-const-volatile-quali
    bool operator()(T& v1, T& v2) const     
    {
        return v1 < v2;
    }
};

template <typename E, typename C>			// quick-sort S
void quickSort(std::vector<E>& S, const C& less) {
    if (S.size() <= 1) return;				        // already sorted
    quickSortStep(S, 0, S.size() - 1, less);		// call sort utility
}

//
// A subsequence of the input sequence is implicitly represented by a range of [l,r]
// The divide step is performed by scanning the array simultaneously from l forward and from r backward,
// swapping pairs of elements that are in reverse order(l > r) => (r < l).
// In-place quick-sort reduces the running time caused by the creation of new sequences and the movement of elements by a constant factor.
// STL's sorting algorithm is based in part on quick-sort
// 
template <typename E, typename C>
void quickSortStep(std::vector<E>& S, int a, int b, const C& less) {
    if (a >= b) return;				// 0 or 1 left? done
    E pivot = S[b];					// select last as pivot
    int l = a; 						// index l scans the sequence from left to right 
    int r = b - 1;					// index r scans the sequence from right to left
    while (l <= r) {
        while (l <= r && !less(pivot, S[l])) l++;		// scan right till larger
        while (r >= l && !less(S[r], pivot)) r--;		// scan left till smaller
        if (l < r)					// both elements found
            std::swap(S[l], S[r]);
    }							// until indices cross
    std::swap(S[l], S[b]);				// store pivot at l

    
    quickSortStep(S, a, l - 1, less);			// recur on both sides
    quickSortStep(S, l + 1, b, less);
}

// Note the difference between l<r and S[l]<S[r]


int main()
{
    less<int> lessthan;
    
    std::vector<int> vector = { 1,5,4,2,3,6,141,53,6,14341,635 };

    

    std::cout << "Before quick sort: " << std::endl;
    for (int i = 0; i < vector.size(); ++i)
    {    
        std::cout << "element is : " << vector[i] << std::endl;
    }

    // quick sort
    quickSort(vector, lessthan);
    std::cout << "==================" << std::endl;
    std::cout << "After quick sort: " << std::endl;
    for (int i = 0; i < vector.size(); ++i)
    {
        std::cout << "element is : " << vector[i] <<  std::endl;
    }
    
}