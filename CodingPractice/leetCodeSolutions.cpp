#include "leetCodeSolutions.h"
#include "SortAlgorithms.h"

vector<int> LeetCodeSolution::twoSum(vector<int>& a_nums, int a_target)
{
	assert(a_nums.size() != 0 && a_target != NULL);
	unordered_map<int, int> m;
	vector<int> res;
	for (int i = 0; i < a_nums.size(); ++i) {
		m[a_nums[i]] = i;
	}
	for (int i = 0; i < a_nums.size(); ++i) {
		int t = a_target - a_nums[i];
		if (m.count(t) && m[t] != i) {
			res.push_back(i);
			res.push_back(m[t]);
			break;
		}
	}
	return res;
}

std::vector<std::vector<int>> LeetCodeSolution::threeSum(vector<int>& a_nums, int a_target)
{
	assert(a_nums.size() != 0);
	SortVector(a_nums);

	set<vector<int>> result;

	for (int k = 0; k < a_nums.size(); k++)
	{
		if (a_nums[k] > 0 ) break;
		int target = a_target - a_nums[k];
		int i = k + 1, j = a_nums.size() - 1;
		while (i < j) {
			if (a_nums[i] + a_nums[j] == target) {
				result.insert({ k, i, j });
				while (i < j && a_nums[i] == a_nums[i + 1]) ++i;
				while (i < j && a_nums[j] == a_nums[j - 1]) --j;
				++i; --j;
			}
			else if (a_nums[i] + a_nums[j] < target) ++i;
			else --j;
		}
		
	}

	return vector<vector<int>>(result.begin(),result.end());

}

bool LeetCodeTest::twoSum_Test()
{
	vector<int> testset = { 2, 7, 11, 15 };
	int target = 18;

	vector<int> result = LeetCodeSolution::twoSum(testset, target);

	int sum = 0;
	for (int i : result)
		sum += testset[i];

	if (sum == target)
		return true;

	return false;
}

bool LeetCodeTest::threeSum_Test()
{
	vector<int> testset = { -1 ,0 ,1 ,2 ,- 1, - 4 };
	int target = 0;

	vector<vector<int>> result = LeetCodeSolution::threeSum(testset, target);

	if (!result.size())
		return false;

	bool pass = true;
	for (vector<int> i : result)
	{
		int sum = 0;
		for (int j : i)
			sum += testset[j];
		pass = pass && (sum == target);
	}

	return pass;
}