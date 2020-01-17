#include "priority_queue.hpp"
#include <iostream>
using namespace std;

// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity)
{
	heap = new TaskItem *[n_capacity + 1];
	capacity = n_capacity;
	size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue()
{
	while (size)
	{
		delete heap[size];
		size--;
	}
	delete[] heap;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const
{
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const
{
	return size == 0;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const
{
	return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const
{
	cout << "Current Max Heap" << endl
		 << endl;
	for (int i = 1; i <= size; i++)
	{
		cout << "Node: " << i << " Priority: " << heap[i]->priority << endl;
	}
	cout << endl;
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const
{
	if (empty())
		return TaskItem(-1, "NULL");
	else
		return *heap[1];
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue(TaskItem val)
{
	if (size == capacity)
		return false;

	if (size == 0)
		heap[1] = new TaskItem(val);

	else
	{
		int indexNewItem = size + 1;
		heap[indexNewItem] = new TaskItem(val);

		while (indexNewItem > 1 && heap[indexNewItem / 2]->priority < heap[indexNewItem]->priority)
		{
			TaskItem *temp = heap[indexNewItem];
			heap[indexNewItem] = heap[indexNewItem / 2];
			heap[indexNewItem / 2] = temp;
			indexNewItem /= 2;
		}
	}
	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue()
{
	if (size == 0)
		return false;

	delete heap[1];
	heap[1] = heap[size];
	unsigned int index = 1;

	bool balanced = false;

	while (2 * index <= size && index >= 1 && !balanced)
	{
		int max_index;

		if (2 * index == size)
			max_index = 2 * index;
		else
			heap[2 * index]->priority >= heap[2 * index + 1]->priority ? max_index = 2 *index : max_index = 2 * index + 1;

		if (heap[max_index]->priority > heap[index]->priority)
		{
			TaskItem *temp = heap[max_index];
			heap[max_index] = heap[index];
			heap[index] = temp;
			index = max_index;
		}
		else
			balanced = true;
	}

	heap[size] = NULL;
	size--;
	return true;
}
