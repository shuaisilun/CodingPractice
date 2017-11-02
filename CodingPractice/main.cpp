//=======================includes===================================
#include <stddef.h>
#include <iostream>

#include "AlgorithmTest.h"
#include "SortAlgorithms.h"
#include "ThreadManager.h"
#include "leetCodeSolutions.h"
#include "DataStructures.h"

#include "SuedoCode.h"

//=======================Defines====================================
#define DEBUG_PRINT_LINE_FUNC(BaseName)   char* fileName##BaseName = __FILE__;								\
								char* temp##BaseName = fileName##BaseName;									\
								while (*(temp##BaseName++) != '\0')								\
								{	fileName##BaseName = *temp##BaseName == '\\' ? temp##BaseName + 1: fileName##BaseName; }\
								printf("%s:%d %s \n", fileName##BaseName, __LINE__, __FUNCTION__)




#define TESTSET_SIZE 10

#define LEETTESTPRINT(testfunc, name) printf(name) ; printf(" test : %s \n", testfunc ? "Succeed": "Failed" );
//==================================================================

static int TestSet[TESTSET_SIZE] = //{ 3,4,5,6,8 };
{ 10,5,3,8,4,9,6,1,2,7 };
//------------------------------------------
// Test function Begin
//------------------------------------------

//Test if a int list is an incresing set
bool IncreasiveSet(int* a_testSet, int a_size)
{
	for (int i = 0; i < (a_size - 1); i++)
	{
		if (a_testSet[i] > a_testSet[i + 1])
			return false;
	}
	return true;
}
//------Testing--Function--End--------------

//==========Diferent==Kind==of=test=========
void PerformAlgorithmTest()
{
	int* testCase = new int[TESTSET_SIZE];

	for (int i = 0; i < TESTSET_SIZE; i++)
	{
		testCase[i] = TestSet[i];
	}

	static AlgorithmTest mytest(&testCase[0], &IncreasiveSet, TESTSET_SIZE);

	ThreadManager::Instance().async([]() {mytest.SetSortFuc(&BubbleSort); mytest.Test(); });

	ThreadManager::Instance().async([]() {mytest.SetSortFuc(&SelectionSort); mytest.Test(); });

	ThreadManager::Instance().async([]() {mytest.SetSortFuc(&QuickSort); mytest.Test(); });
}

bool testcheck(int a_in[], int a_size)
{

}
//==========================================
// Start
int main(void)
{
	const char* meName = "Allen";
	printf("hello %s \n", meName);

	vector<int> testSet(10, 5, 3, 8, 4, 9, 6, 1, 2, 7);

	// doodling
	{
		//new ThreadManager(8);
		//PerformAlgorithmTest();
	}

	//leetCode test
	{
		//LeetCodeTest::twoSum_Test();
		//LeetCodeTest::threeSum_Test();
		//LeetCodeTest::AddTwoNumbers_Test();
		//LeetCodeSolution::isIsomorphic(string("egg"), string("add"));
		//LeetCodeSolution::isIsomorphic(string("paper"), string("title"));
		//string s = LeetCodeSolution::longestPalindrome(string("asdlfjkasnellanoonallenjdklfajsdjf"));
	}

	//busy waiting to prevent close the terminal.
	while (1)
		NULL;

	return 0;
}