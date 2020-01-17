#include <iostream>
#include <stack>
#include <algorithm>
#include "binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree()
{
	root = NULL;
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree()
{
	stack<TaskItem *> s;
	s.push(root);

	while (!s.empty())
	{
		TaskItem *temp = s.top();
		s.pop();
		if (temp->right)
			s.push(temp->right);
		if (temp->left)
			s.push(temp->left);

		delete temp;
		temp = NULL;
	}
	root = NULL;
	size = 0;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const
{
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const
{
	if (get_size() == 0)
		return BinarySearchTree::TaskItem(-1, "N/A");

	TaskItem *temp = root;

	while (temp->right)
		temp = temp->right;

	return *temp;
}

// PURPOSE: helper
BinarySearchTree::TaskItem *BinarySearchTree::min(TaskItem *start) const
{
	TaskItem *temp = start;

	while (temp->left)
		temp = temp->left;

	return temp;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const
{
	if (get_size() == 0)
		return BinarySearchTree::TaskItem(-1, "N/A");

	TaskItem *temp = root;

	while (temp->left)
		temp = temp->left;

	return *temp;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const
{
	return get_node_depth(root);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const
{
	stack<TaskItem *> s;
	s.push(root);

	while (!s.empty())
	{
		TaskItem *temp = s.top();
		s.pop();
		cout << "Priority: " << temp->priority << " Description: " << temp->description;
		if (temp->right)
			s.push(temp->right);
		if (temp->left)
			s.push(temp->left);
	}
}

// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const
{
	if (size == 0)
		return false;
	else if (size == 1)
		return root->priority == val.priority;

	TaskItem *temp = root;

	while (temp)
	{
		if (temp->priority == val.priority)
			return true;

		if (temp->priority < val.priority)
			temp = temp->right;
		else
			temp = temp->left;
	}

	return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem *BinarySearchTree::get_root_node()
{
	return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem **BinarySearchTree::get_root_node_address()
{
	return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth(BinarySearchTree::TaskItem *n) const
{
	if (n == NULL)
		return -1;

	return 1 + std::max(get_node_depth(n->left), get_node_depth(n->right));
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert(BinarySearchTree::TaskItem val)
{
	if (get_size() == 0)
	{
		*root = val;
		return true;
	}

	TaskItem *temp = root;

	while (temp)
	{
		if (temp->priority == val.priority)
			return false;
		else if (temp->priority > val.priority)
		{
			if (!(temp->left))
			{
				temp->left = new TaskItem(val);
				temp = NULL;
				continue;
			}
			temp = temp->left;
		}
		else
		{
			if (!(temp->right))
			{
				temp->right = new TaskItem(val);
				temp = NULL;
				continue;
			}
			temp = temp->right;
		}
	}
	++size;
	return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove(BinarySearchTree::TaskItem val)
{
	if (!exists(val))
		return false;

	TaskItem *parent;
	TaskItem *temp = root;
	bool leftTree = false;

	while (temp)
	{
		if (temp->priority == val.priority)
			break;

		parent = temp;

		if (temp->priority < val.priority)
		{
			temp = temp->right;
			leftTree = false;
		}
		else
		{
			temp = temp->left;
			leftTree = true;
		}
	}

	if (!(temp->right) && !(temp->left))
	{
		delete temp;
		leftTree ? parent->left = NULL : parent->right = NULL;
	}
	else if (temp->right || temp->left)
	{
		if (temp->left)
			leftTree ? parent->left = temp->left : parent->right = temp->left;
		else
			leftTree ? parent->left = temp->right : parent->right = temp->right;
		delete temp;
	}
	else
	{
		TaskItem *succ = min(temp->right);
		temp->priority = succ->priority;
		temp->description = succ->description;
		temp->right->left = succ->right;
		delete succ;
	}
	--size;
	return true;
}
