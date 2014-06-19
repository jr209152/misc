// Author: Kenji Hata
// Copyright: May 2014
 
#include "BinomialHeap.h"
#include "error.h"
#include <iostream>;

BinomialHeap::BinomialHeap() {
	sizeNum = 0;
}

BinomialHeap::~BinomialHeap() {
	/* Iterates through each head in the vector and removes it and all of its children */
	foreach(Node* head in heap)
	{
		recursiveDelete(head);
	}
}

void BinomialHeap::recursiveDelete(BinomialHeap::Node*& nod)
{
	if(nod != NULL)
	{
		/* Iterates through each head in the vector and removes it and all of its children */
		foreach(Node* head in nod->children)
		{
			recursiveDelete(head);
		}
		delete nod;
	}
}

int BinomialHeap::size() {
	return sizeNum;
}

bool BinomialHeap::isEmpty() {
	return size()==0;
}

void BinomialHeap::enqueue(string value) {
	/*creates a new Node with an empty vector */
	Node* newNode = new Node;
	newNode->str = value;
	Vector<Node*> temp;
	newNode->children = temp; 

	/*if the heap is empty then add it*/
	if (isEmpty())
		heap.add(newNode);

	/* if not, merge this new heap with the old one */
	else
	{
		Vector<Node*> tempheap;
		tempheap.add(newNode);
		mergeHeap(heap, tempheap);
	}
	sizeNum++;
}

string BinomialHeap::peek() {
	/* if empty, output an error */
	if(isEmpty())
		error("There are no elements in the Priority Queue");

	/* finds the first heap, and sets it as the temporary minimum */
	int index;
	for (int i=0; i<heap.size(); ++i)
	{
		if (heap.get(i)!=NULL)
		{
			index = i;
			break;
		}
	}
	string min = heap.get(index)->str;

	/*finds the minimum */
	for(int j=index; j<heap.size(); ++j)
	{
		if (heap.get(j)!= NULL && heap.get(j)->str < min)
			min = heap.get(j)->str;
	}
	return min;
}

string BinomialHeap::dequeueMin() {
	/* Operates just like peek for the beginning */
	if(isEmpty())
		error("There are no elements in the Priority Queue");
	int index;
	for (int i=0; i<heap.size(); ++i)
	{
		if (heap.get(i)!=NULL)
		{
			index = i;
			break;
		}
	}
	string min = heap.get(index)->str;
	for(int j=index; j<heap.size(); ++j)
	{
		if (heap.get(j)!= NULL && heap.get(j)->str < min)
		{
			index = j;
			min = heap.get(j)->str;
		}
	}

	/* removes the minimum node and merges it's children with the old heap */
	Vector<Node*> temp = heap.get(index)->children;
	heap.removeAt(index);
	mergeHeap(heap, temp);
	sizeNum--;
	return min;
}

void BinomialHeap::mergeHeap(Vector<BinomialHeap::Node*>& lhs, Vector<BinomialHeap::Node*>& rhs){
	Vector<Node*> combine;
	int maxSize = max(lhs.size(), rhs.size());
	lhs = resize(lhs, maxSize);
	rhs = resize(rhs, maxSize);
	Node* carry = NULL;
	for (int i=0; i<maxSize; i++)
	{
		/* if both heaps are NULL, then use the carry, and set the carry to NULL */
		if(lhs.get(i)==NULL && rhs.get(i)==NULL)
		{
			combine.add(carry);
			carry = NULL;
		}

		/* if one of the heaps is NULL... 
		1) if there is no carry, add that non-NULL heap
		2) if there is a carry, add NULL, and make a new carry 
		*/
		else if (rhs.get(i)==NULL)
		{
			if(carry == NULL)
				combine.add(lhs.get(i));
			else
			{
				carry = mergeNode(lhs.get(i), carry);
				combine.add(NULL);
			}
		}
		else if (lhs.get(i)==NULL)
		{
			if(carry == NULL)
				combine.add(rhs.get(i));
			else
			{
				carry = mergeNode(rhs.get(i), carry);
				combine.add(NULL);
			}
		}

		/* if both are non-NULL, then add the carry and set the carry to the merge of the two nodes */
		else
		{
			combine.add(carry);
			carry = mergeNode(lhs.get(i), rhs.get(i));	
		}
	}
	if(carry!=NULL)
		combine.add(carry);
	rhs.clear();
	lhs = combine;
}

BinomialHeap::Node* BinomialHeap::mergeNode(Node* lhs, Node* rhs)
{
	/* puts the bigger node as the child node */
	if(lhs->str < rhs->str)
	{
		lhs->children.add(rhs);
		return lhs;
	}
	else
	{
		rhs->children.add(lhs);
		return rhs;
	}
}
Vector<BinomialHeap::Node*> BinomialHeap::resize(Vector<BinomialHeap::Node*> vec, int num)
{
	/*resizes the vector by a certain amount */
	for(int j=0; j<num; j++)
	{
		vec.add(NULL);
	}
	return vec;
}



