//Another way to prevent duplicate include
#ifndef __ALGORITHMTEST__
#define __ALGORITHMTEST__

#include <iostream>
#include <atomic>
#include <mutex>
#include <functional>

using namespace std;

static mutex g_PrintMutex;

class AlgorithmTest
{
public:
	AlgorithmTest(int*, bool (*testFunc) (int*,int),int);
	~AlgorithmTest();
	
	void SetSortFuc(int* (*sortFunc) (int*,const int)) { m_SortFunc = sortFunc; }

	bool Test();

	static void PrintIntList(int*,int);

private:
	//Data
	int* m_testSet;
	bool(*m_testFunc) (int*,int);

	int* (*m_SortFunc) (int*,const int);
	int m_size;
};
#endif // __ALGORITHMTEST__