#include "leetCodeSolutions.h"
#include "SortAlgorithms.h"


#define  max(a,b) a>b?a :b

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

LinkListNode<int>* LeetCodeSolution::addtwoNumbers(LinkListNode<int>* a_l1, LinkListNode<int>* a_l2)
{
	auto l1 = a_l1;
	auto l2 = a_l2;

	auto result = new LinkListNode<int>();

	int carry = 0;

	while (l1 || l2)
	{
		int n1 = l1 ? l1->getVal(): 0;
		int n2 = l2 ? l2->getVal(): 0;
		int sum = n1 + n2 + carry;
		carry = sum / 10;
		result->insert(sum % 10);
		if (l1) l1 = l1->next;
		if (l2) l2 = l2->next;
	}

	if (carry) result->insert(1);

	return result;
}

int LeetCodeSolution::lengthOfLongestSubstring(string s)
{
	int m[256] = { 0 }, res = 0, left = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (m[s[i]] == 0 || m[s[i]] < left) {
			res = max(res, i - left + 1);
		}
		else {
			left = m[s[i]];
		}
		m[s[i]] = i + 1;
	}
	return res;
}

bool LeetCodeSolution::isIsomorphic(string s, string t)
{
	int m1[256] = { 0 }, m2[256] = { 0 }, n = s.size();
	for (int i = 0; i < n; ++i) {
		if (m1[s[i]] != m2[t[i]]) return false;
		m1[s[i]] = i + 1;
		m2[t[i]] = i + 1;
	}
	return true;
}


void LeetCodeSolution::searchPlindrome(string s, int left, int right, int& startIndex, int& len)
{
	bool finished = false;
	int tempLeft = left;
	int tempLen = 0;
	if (left != right)
		tempLen +=2;
	int startLen = tempLen;
	while (!finished)
	{
		if (left == 0 || right == s.size() || s[--left] != s[++right])
			finished = true;
		else
			tempLen += 2;
	}

	if (tempLen !=0 && tempLen > len)
	{
		startIndex = left == 0 || right==s.size() ? 0: left + 1;
		len = tempLen;
		string m = s.substr(startIndex, len);
	}
}

bool LeetCodeSolution::isMatch(string s, string p)
{
	if (p.empty()) return s.empty();
	if (p.size() == 1) {
		return (s.size() == 1 && (s[0] == p[0] || p[0] == '.'));
	}
	if (p[1] != '*') {
		if (s.empty()) return false;
		return (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1));
	}
	while (!s.empty() && (s[0] == p[0] || p[0] == '.')) {
		if (isMatch(s, p.substr(2))) return true;
		s = s.substr(1);
	}
	return isMatch(s, p.substr(2));
}

std::string LeetCodeSolution::longestPalindrome(string s)
{
	int nsize = s.size() , left = 0, right =0, len= 0, startIndex = 0;

	for (int i = 0; i < nsize; i++)
	{
		if (s[i] == s[i + 1])
		{
			left = i; 
			right = i + 1;
			searchPlindrome(s, left, right, startIndex, len);
		}
		else
		{
			left = i;
			right = i;
			searchPlindrome(s, left, right, startIndex, len);
		}
	}

	if (!len) len = s.size();
	return s.substr(startIndex, len);
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

bool LeetCodeTest::AddTwoNumbers_Test()
{
	LinkListNode<int>* l1 = new LinkListNode<int>();
	LinkListNode<int>* l2 = new LinkListNode<int>();

	int testset[3] = { 2,4,3 };
	int testset2[3] = { 5,6,4 };

	for (int i : testset)
		l1->insert(i);

	for (int i : testset2)
		l2->insert(i);

	LinkListNode<int>* result = LeetCodeSolution::addtwoNumbers(l1, l2);
	
	int expectedResult[3] = { 7,0,8 };

	bool pass = true;
	auto tempNode = result;
	for (int i : expectedResult)
	{
		pass = pass && (i == tempNode->getVal());
		if (!pass)
			break;
		else
			tempNode = tempNode->next;
	}

	return pass;
}
