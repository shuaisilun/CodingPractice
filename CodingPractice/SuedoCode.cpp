#include "SuedoCode.h"
//1.把二元查找树转变成排序的双向链表（树）
//========================================================
// find the min value of sorted bstree
BSTreeNode* InsertBS(BSTreeNode* a_head, int a_value)
{
	if (a_head->m_Value > a_value)
	{
		if (a_head->left)
			InsertBS(a_head->left, a_value);
		else
		{
			BSTreeNode* newNode = new BSTreeNode(a_value);
			a_head->left = newNode;
		}
	}
	if (a_head->m_Value < a_value)
	{
		if (a_head->right)
			InsertBS(a_head->right, a_value);
		else
		{
			BSTreeNode* newNode = new BSTreeNode(a_value);
			a_head->right = newNode;
		}
	}

	return a_head;
}

BSTreeNode* tranBS(BSTreeNode* a_head, BSTreeNode* a_pre)
{
	BSTreeNode* tempLeft = nullptr;
	BSTreeNode* tempRight = nullptr;
	if (a_head->left)
		tempLeft = tranBS(a_head->left,a_head);
	if (a_head->right)
		tempRight = tranBS(a_head->right,a_head);

	a_head->left = tempLeft;
	a_head->right = tempRight;
	if (tempLeft)
		tempLeft->right = a_head;
	if (tempRight)
		tempRight->left = a_head;

	BSTreeNode* tempNode = a_head;
	if (a_pre)
	{
		if (a_pre->left == a_head)
			while (tempNode->right)
				tempNode = tempNode->right;
		if (a_pre->right == a_head)
			while (tempNode->left)
				tempNode = tempNode->left;
		return tempNode;
	}

	while (tempNode->left)
		tempNode = tempNode->left;

	return tempNode;
}

//========================================================