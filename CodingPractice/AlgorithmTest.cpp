#include "AlgorithmTest.h"
#include <stdio.h>

//------------------------------------------
// Constructor
//------------------------------------------
AlgorithmTest::AlgorithmTest(int* testSet, bool (*testFunc) (int*,int), int size)
		:	m_testSet(testSet),
			m_testFunc(testFunc), 
			m_size(size)
{
}

//------------------------------------------
// Destructor
//------------------------------------------
AlgorithmTest::~AlgorithmTest()
{
	delete[]m_testSet;
}


//------------------------------------------
// Test
//------------------------------------------
bool AlgorithmTest::Test()
{
	if (!m_SortFunc || m_size == 0 || !m_testSet)
		return false;
	
	int* sortResult = new int[m_size];
	memcpy(sortResult,m_testSet,sizeof(int)* m_size);

	m_SortFunc(sortResult, m_size);

	bool testResult = m_testFunc(sortResult,m_size);

	{
		lock_guard<mutex> printLock(g_PrintMutex);
		printf("%s", testResult ? "Succeed :)" : "Failed :(");

		int *temp = sortResult;

		printf(" Result ");
		PrintIntList(temp, m_size);
		printf("\n \n");
	}

	delete[] sortResult;

	return testResult;
}

//------------------------------------------
// Static PrintIntList
//------------------------------------------
void AlgorithmTest::PrintIntList(int* a_list, int a_size)
{
	printf("[");
	for (int i = 0; i < a_size; i++)
	{
		if (i == (a_size - 1))
		{
			printf("%i", a_list[i]);
		}
		else
		{
			printf("%i,", a_list[i]);
		}
	}
	printf("]");
}

