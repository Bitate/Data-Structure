#include <iostream>
#include <vector>
using namespace std;

void merge(int arr[], int startIndex, int middleIndex, int endIndex)
{
    // Numbers of elements that will be sorted from startIndex until endIndex.
    int totalNumbers = endIndex - startIndex + 1;

    // Temporary array to store merged array.
    int* tempArray = new int[totalNumbers];

    // Index of left subarray array[startIndex ... middleIndex]
    int leftIndex = startIndex;

    // Index of right subarray array[middleIndex ... endIndex]
    int rightIndex = middleIndex + 1;

    // Index of merged array
    int mergedIndex = 0;

    // Merge two subarrays
    // Left subarray: [startIndex, middleIndex]
    // Right subarray: (middleIndex, endIndex]
    while (leftIndex <= middleIndex && rightIndex <= endIndex)
    {
        if (arr[leftIndex] <= arr[rightIndex])
        {
            // Store the left subarray's element if it's less than the right one
            tempArray[mergedIndex] = arr[leftIndex];
            // Go to next left subarray index
            ++leftIndex;
        }
        else
        {
            // Store the right subarray's element if it's less than the left one
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
        arr[startIndex++] = tempArray[i];
    }

    // Delete the temporary array "tempArray"
    delete[] tempArray;
}

void mergeSort(int arr[], int startIndex, int endIndex)
{
	// Only do merge stort if the end index is greater than start index
	if (endIndex > startIndex)
	{
		// Find middle index
		int middleIndex = (startIndex + endIndex) / 2;

		// Sort left subarray:  [startIndex ... middleIndex]
		mergeSort(arr, startIndex, middleIndex);

		// Sort right subarray: (middleIndex ... endIndex]
		mergeSort(arr, middleIndex+1, endIndex);

		// Merge the left and the right subarray
		merge(arr, startIndex, middleIndex, endIndex);
	}
}

int main()
{
    constexpr int arr_size = 10;
	int arr[arr_size] = { 2,1,8,230,48,590,193,194,1222,655535};
	mergeSort(arr, 0, arr_size-1);
	
    for (auto e : arr)
		cout << e << " ";
	cout << endl;
}