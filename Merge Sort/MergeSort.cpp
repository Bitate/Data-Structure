


void merge(int arr[], int startIndex, int middleIndex, int endIndex)
{
	// Numbers of elements that will be sorted
	// from startIndex until endIndex
	int totalElements = endIndex - startIndex + 1;

	// Temporary array to store merged array
	int* tempArr = new int[totalElements];

	// Index of left subarray
	// arr[startIndex ... middleIndex]
	int leftIndex = startIndex;

	// Index of right subarray
	// arr[middleIndex ... endIndex]
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
			tempArr[mergedIndex] = arr[leftIndex];

			// Go to next left subarray index
			++leftIndex;
		}
		else
		{
			// Store the right subarray's element
			// if it's less than the left one
			tempArr[mergedIndex] = arr[rightIndex];

			// Go to next right subarray index.
			++rightIndex;
		}

		// Go to next merged array index
		++mergedIndex;
	}

	// If there are any remaining elements in left subarray
	// that is not stored into merged array yet
	while (leftIndex <= middleIndex)
	{
		tempArr[mergedIndex] = arr[leftIndex];

		// Go to next left subarray index
		++leftIndex;

		// Go to next merged array index
		++mergedIndex;
	}

	// If there are any remaining elements in right subarray
	// that is not stored into merged array yet
	while (rightIndex <= endIndex)
	{
		tempArr[mergedIndex] = arr[rightIndex];

		// Go to next right subarray index
		++rightIndex;

		// Go to next merged array index
		++mergedIndex;
	}

	// Finally, copy the elements in tempArr to the original array
	for (int i = 0; i < totalElements; ++i)
	{
		arr[i] = tempArr[i];
	}

	// Remove the tempArr array 
	delete[] tempArr;

	return;
}

void mergeSort(int arr[], int startIndex, int endIndex)
{
	// Only do merge stort 
	// if the end index is greater than start index
	if (endIndex > startIndex)
	{
		// Find middle index
		int middleIndex = (startIndex + endIndex) / 2;

		// Sort left subarray
		// arr[startIndex ... middleIndex]
		mergeSort(arr, startIndex, middleIndex);

		// Sort right subarray
		// arr[middleIndex ... endIndex]
		mergeSort(arr, middleIndex, endIndex);

		// Merge the left and the right subarray
		merge(arr, startIndex, middleIndex, endIndex);
	}

	return;
}