//
// Merge Sort Based on STL list
//

#include <list>
#include <functional>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
struct lessthan
{
    // Don't omit const keyword, click below link for why
    // https://stackoverflow.com/questions/19816139/expression-having-type-const-comparevptrs-would-lose-some-const-volatile-quali
    bool operator()(T& v1, T& v2) const
    {
        return v1 < v2;
    }
};

template <typename E, typename C>
void mergeSort(list<E>& S, const C& less) {
    typedef typename list<E>::iterator Itor;		// sequence of elements
    int n = S.size();                               // S is the original Sequence, 
                                                    // not the result sequence S
    if (n <= 1) return;					            // already sorted
    list<E> S1, S2;
    Itor p = S.begin();
    for (int i = 0; i < n / 2; i++) S1.push_back(*p++);	// copy first half to S1
    for (int i = n / 2; i < n; i++) S2.push_back(*p++);	// copy second half to S2
    S.clear();						    // clear S's contents
    mergeSort(S1, less);				// recur on first half
    mergeSort(S2, less);				// recur on second half
    merge(S1, S2, S, less);				// merge S1 and S2 into S
}

template <typename E, typename C>			// merge utility
void merge(list<E>& S1, list<E>& S2, list<E>& S, const C& less) {
    typedef typename list<E>::iterator Itor;		// sequence of elements
    Itor p1 = S1.begin();
    Itor p2 = S2.begin();
    while (p1 != S1.end() && p2 != S2.end()) {		// until either is empty
        if (less(*p1, *p2)) 				        // append smaller to S
            S.push_back(*p1++);
        else
            S.push_back(*p2++);
    }
    while (p1 != S1.end())				// copy rest of S1 to S
        S.push_back(*p1++);
    while (p2 != S2.end())				// copy rest of S2 to S
        S.push_back(*p2++);
}




/**
 * Merge Sort
 *
 * We need to have two functions to perform a merge sort
 *
 * First: Merge()
 *      This function is used when each half part has been sorted.
 *
 * Second: MergeSort()
 *      This function is used to seperate the array into two sublists/subarraies
 */

void Merge(
    int arr[],
    int startIndex,
    int middleIndex,
    int endIndex
)
{
    // Numbers of elements that will 
    // be sorted from startIndex until
    // endIndex.
    int totalNumbers = endIndex - startIndex + 1;

    // Temporary array to store merged array.
    int* tempArray = new int[totalNumbers];

    // Index of left subarray
    // array[startIndex ... middleIndex]
    int leftIndex = startIndex;

    // Index of right subarray
    // array[middleIndex ... endIndex]
    int rightIndex = middleIndex + 1;

    // Index of merged array
    int mergedIndex = 0;

    // Merge two subarrays
    while (leftIndex <= middleIndex && rightIndex <= endIndex)
    {
        if (arr[leftIndex] <= arr[rightIndex])
        {
            // Store the left subarray's element
            // if it's less than the right one
            tempArray[mergedIndex] = arr[leftIndex];

            // Go to next left subarray index
            ++leftIndex;
        }
        else
        {
            // Store the right subarray's element
            // if it's less than the left one
            tempArray[mergedIndex] = arr[rightIndex];

            // Go to next right subarray index
            ++rightIndex;
        }

        // Go to next merged array index
        ++mergedIndex;
    }
    // If there are any remaining elements in left subarray
        // that is not sorted into merged array yet
    while (leftIndex <= middleIndex)
    {
        tempArray[mergedIndex] = arr[leftIndex];

        // Go to next left subarray index
        ++leftIndex;

        // Go to next merged array index
        ++mergedIndex;
    }

    // If there are any remaining elements in right subarray
    // that is not sorted into merged array yet
    while (rightIndex <= endIndex)
    {
        tempArray[mergedIndex] = arr[rightIndex];

        // Go to next right subarray index
        ++rightIndex;

        // Go to next merged array index
        ++mergedIndex;
    }

    // Now, the merged array has been sorted.
    // Copy the elements to the original array
    for (int i = 0; i < totalNumbers; ++i)
    {
        arr[startIndex + 1] = tempArray[i];
    }

    // Delete the temporary array "tempArray"
    delete[] tempArray;

    return;
}


void MergeSort(
    int arr[],
    int startIndex,
    int endIndex
)
{

}















int main()
{
    lessthan<int> lessthan;

    std::list<int> list = { 1,5,4,2,3,6,141,53,6,14341,635 };
    std::list<int>::iterator itBegin = list.begin();
    
    cout << "Before Merge Sort" << endl;
    for (int i = 0; i < list.size(); ++i)
    {
        auto it = std::next(itBegin, i);
        cout << *it << endl;
    }

    cout << "After Merge Sort" << endl;
    cout << ">>>>>>>>>>>>>>>>>>" << endl;


    
}