#pragma once
#include <iostream>

#include <assert.h>

#include <vector>
#include <unordered_map>
#include <set>

#include "DataStructures.h"

using namespace std;

namespace LeetCodeSolution
{
vector<int> twoSum(vector<int>& a_nums, int a_target);

vector<vector<int>> threeSum(vector<int>& a_nums, int a_target);

LinkListNode<int>* addtwoNumbers(LinkListNode<int>* a_l1, LinkListNode<int>* a_l2);

int lengthOfLongestSubstring(string s);

bool isIsomorphic(string s, string t);
}

namespace LeetCodeTest
{
	bool twoSum_Test();
	bool threeSum_Test();
	bool AddTwoNumbers_Test();
}