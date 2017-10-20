// to prevent duplicate include
#ifndef __SORTINGALGORITHMS__
#define __SORTINGALGORITHMS__
#include <assert.h> 
#include <vector>



int* BubbleSort(int* a_Input, int a_size);

int* SelectionSort(int* a_Input, int a_size);

int* QuickSort(int* a_Input, int a_size);

int* QuickSort(int* a_arr, int a_left, int a_right, int& o_numCompQuickSort, int& o_numSwapQuickSort);

void SortVector(std::vector<int>& a_nums);
#endif
