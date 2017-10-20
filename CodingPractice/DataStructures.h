#pragma once

#include <assert.h>

template<typename T>
class LinkListNode
{
public:
	LinkListNode()
	{
		m_data = NULL;
		pre = nullptr;
		next = nullptr;
	}

	~LinkListNode()
	{
		delete &m_data;
		if (next)
			delete next;
	};

	void insert(T a_in, LinkListNode<T>* a_pre = nullptr)
	{
		if (!pre && m_data == NULL && !next)
			m_data = a_in;
		else if (next)
			next->insert(a_in, this);
		else
		{
			LinkListNode* newNode = new LinkListNode();
			next = newNode;
			next->pre = this;
			next->m_data = a_in;
		}
	}

	T& getVal() { return m_data; }

	T m_data;
	LinkListNode<T>* pre;
	LinkListNode<T>* next;
};