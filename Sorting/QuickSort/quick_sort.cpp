#include <iostream>
#include <vector>

using namespace std;

void quick_sort(vector<int>& data, int start, int end)
{
	// each recursion, we reset the following three variables
	int pivot = data[(start + end) / 2];
	int left = start;
	int right = end;

	// only if left pointer <= right pointer,
	// we perform swaps
	while (left <= right)
	{
		while (data[left] < pivot)
			++left;
		while (data[right] > pivot)
			--right;
		// if after above two loops,
		// left still <= right,
		// which means data[left] > pivot > data[right]
		// we need to perform a swap.
		if (left <= right)
		{
			swap(data[left], data[right]);
			++left;
			--right;
		}
	}

	// recursively quick sort
	// sort left sub-array
	if (start < right)
		quick_sort(data, start, right);
	// sort right sub-array
	if (left < end)
		quick_sort(data, left, end);
}

int main()
{
	vector<int> unsorted_ints = { 132,2,4,3,9,10,34 };
	cout << "Unsorted array: " << endl;
	for (auto e : unsorted_ints)
		cout << e << " ";
	cout << endl;

	quick_sort(unsorted_ints, 0, unsorted_ints.size() - 1);
	cout << "After performing quick-sort: " << endl;
	for (auto e : unsorted_ints)
		cout << e << " ";
	cout << endl;
}