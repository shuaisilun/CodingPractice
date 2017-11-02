#pragma once

#include <assert.h>

#define maxLevel 4
//=========================================================
//				Linked Node
//=========================================================
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
//=========================================================
//					Skip list
//=========================================================
template<class T>
class SkipListNode {
public:
	SkipListNode() {
	}
	T key;
	SkipListNode **next;
};

template<class T>
class SkipList
{
public:
	SkipList();
	bool isEmpty() const;
	void choosePowers();
	int	 chooseLevel();
	T*	 search(const T&);
	void insert(const T&);
private:
	typedef SkipListNode<T> *NodePtr;
	NodePtr root[maxLevel];
	int powers[maxLevel];
};

template<class T>
SkipList<T>::SkipList()
{
	for (int i = 0; i < maxLevel; i++)
		root[i] = nullptr;
}

template<class T>
bool SkipList<T>::isEmpty() const
{
	return root[0] == nullptr;
}

template<class T>
T* SkipList<T>::search(const T&)
{
	if (isEmpty()) return 0;
	NodePtr prev, curr;
	int lvl; // find the highest non-null
	for (lvl = maxLevel - 1; lvl >= 0 && !root[lvl]; lvl--); // level;
	prev = curr = root[lvl];
	while (true)
	{
		if (key == curr->key) // success if equal;
			return &curr->key;
		else if (key < curr->key) { // if smaller, go down
			if (lvl == 0) // if possible,
				return 0;
			else if (curr == root[lvl]) // by one level
				curr = root[--lvl]; // starting from the
			else curr = *(prev->next + --lvl); // predecessor which
		} // can be the root;
		else { // if greater,
			prev = curr; // go to the next
			if (*(curr->next + lvl) != 0) // non-null node
				curr = *(curr->next + lvl); // on the same level
			else { // or to a list on a
				   // lower level;
				for (lvl--; lvl >= 0 && *(curr->next + lvl) == 0; lvl--);
				if (lvl >= 0)
					curr = *(curr->next + lvl);
				else return 0;
			}
		}
	}
}

template<class T>
int SkipList<T>::chooseLevel()
{
	int i, r = rand() % powers[maxLevel - 1] + 1;
	for (i = 1; i < maxLevel; i++)
		if (r < powers[i])
			return i - 1; // return a level < the highest level;
	return i - 1; // return the highest level;
}

template<class T>
void SkipList<T>::insert(const T&)
{
	NodePtr curr[maxLevel], prev[maxLevel], newNode;
	int lvl, i;
	curr[maxLevel - 1] = root[maxLevel - 1];
	prev[maxLevel - 1] = 0;
	for (lvl = maxLevel - 1; lvl >= 0; lvl--) {
		while (curr[lvl] && curr[lvl]->key < key) { // go to the next
			prev[lvl] = curr[lvl]; // if smaller;
			curr[lvl] = *(curr[lvl]->next + lvl);
		}
		if (curr[lvl] && curr[lvl]->key == key) // don’t include
			return; // duplicates;
		if (lvl > 0) // go one level down
			if (prev[lvl] == 0) { // if not the lowest
				curr[lvl - 1] = root[lvl - 1]; // level, using a link
				prev[lvl - 1] = 0; // either from the root
			}
			else { // or from the predecessor;
				curr[lvl - 1] = *(prev[lvl]->next + lvl - 1);
				prev[lvl - 1] = prev[lvl];
			}
	}
	lvl = chooseLevel(); // generate randomly level for newNode;
	newNode = new SkipListNode<T>;
	newNode->next = new NodePtr[sizeof(NodePtr) * (lvl + 1)];
	newNode->key = key;
	for (i = 0; i <= lvl; i++)
	{ // initialize next fields of
		*(newNode->next + i) = curr[i]; // newNode and reset to newNode
		if (prev[i] == 0) // either fields of the root
			root[i] = newNode; // or next fields of newNode’s
		else *(prev[i]->next + i) = newNode; // predecessors;
	}
}
//=========================================================