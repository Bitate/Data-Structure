#include "pch.h"
#include "../Merge Sort/MergeSort.cpp"
#include <iostream>
TEST(MergeSortTest, intNumbers)
{
	//std::cout << "Merge Sort Start: " << std::endl;

	int random[] = { 7, 1, 5, 9, 3, 6, 8, 2 };
	int arrSize = sizeof(random);
	mergeSort(random, 0, arrSize - 1);
	ASSERT_EQ(random[0], 1);
}