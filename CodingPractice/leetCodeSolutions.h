#pragma once
#include <iostream>

#include <assert.h>

#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

namespace LeetCodeSolution
{
vector<int> twoSum(vector<int>& a_nums, int a_target);

vector<vector<int>> threeSum(vector<int>& a_nums, int a_target);
}

namespace LeetCodeTest
{
	bool twoSum_Test();
	bool threeSum_Test();
	bool AddTwoNumbers_Test();
}