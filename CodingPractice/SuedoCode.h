#pragma once

struct BSTreeNode
{
	int m_Value;
	BSTreeNode* left;
	BSTreeNode* right;

	BSTreeNode(int value) : m_Value(value) { left = nullptr; right = nullptr; };
};


BSTreeNode* InsertBS(BSTreeNode* a_head, int a_value);

BSTreeNode* tranBS(BSTreeNode* a_head, BSTreeNode* a_pre = nullptr);