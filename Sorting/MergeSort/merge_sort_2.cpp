#include<iostream>
#include<vector>
using namespace std;

// TODO: Fix array index out of range

// Merge Sort Algorithm (driver)
template<typename Comparable>
void merge_sort(vector<Comparable>& a)
{
	vector<Comparable> tmpArray(a.size());
	merge_sort(a, tmpArray, 0, a.size() - 1);
}

/**
 * Internal method that makes recursive calls.
 * a is an array of Comparable items.
 * tmpArray is an array to place the final merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template<typename Comparable>
void merge_sort(vector<Comparable>& a,
				vector<Comparable>& tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		merge_sort(a, tmpArray, left, center);
		merge_sort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center, right);
	}
}

/**
 * Internal method to merge two sorted halves of a subarray.
 *
 * a is an array of Comparable items.
 * tmpArray is an array to store the final mreged result.
 * left_most is the index of left-most index of the subarray.
 * right_most is the right-most index of the subarray.
 */
template<typename Comparable>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray,
			int left_most, int center, int right_most)
{
	int tmp_pos = left_most;
	int total_nums = right_most - left_most + 1;
	int left = left_most;
	int right = center + 1;
	// main loop
	// Left subarray:  [left_most, center]  
	// Right subarray: (center, left_most]
	while (left <= center && right <= right_most)
	{
		if (a[left] <= a[right])
			tmpArray[tmp_pos++] = std::move(a[left++]);
		else
			tmpArray[tmp_pos++] = std::move(a[right++]);
	}
	
	while (left <= center)
		tmpArray[tmp_pos++] = std::move(a[left++]);
	while (right <= right_most)
		tmpArray[tmp_pos++] = std::move(a[right++]);
	
	// copy tmpArry's elements back to array a.
	for (int i = 0; i < total_nums; ++i, --right)
		a[right] = std::move(tmpArray[right]);
}

int main()
{
	vector<int> unsorted_ints = { 12, 501, 32, 50, 1, 959 };
	merge_sort<int>(unsorted_ints);
	for (auto e : unsorted_ints)
		cout << e << " ";
	cout << endl;
}