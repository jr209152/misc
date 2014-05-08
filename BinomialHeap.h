#ifndef BINOMIAL_HEAP
#define BINOMIAL_HEAP

#include <string>
#include <vector.h>
using namespace std;

class BinomialHeap {
public:
	/* Constructs a new, empty binomial heap. */
	BinomialHeap();
	
	/* Cleans up all memory allocated by this binomial heap. */
	~BinomialHeap();
	
	/* Returns the number of elements in the binomial heap. */
	int size();
	
	/* Returns whether or not the binomial heap is empty. */
	bool isEmpty();
	
	/* Enqueues a new string into the binomial heap. */
	void enqueue(string value);
	
	/* Returns, but does not remove, the lexicographically first string in the
	 * binomial heap.
	 */
	string peek();
	
	/* Returns and removes the lexicographically first string in the
	 * binomial heap.
	 */
	string dequeueMin();

private:
	/* keeps track of the size*/
	int sizeNum;

	/* Each Node keeps track of a string and a vector for all it's children */
	struct Node{
		string str;
		Vector<Node *> children;
	};

	/* Deletes the node and all it's children */
	void recursiveDelete(Node*& nod);

	/* Contains all the binomial heaps */
	Vector<Node*> heap;

	/* merges two Vectors - has the properties of carrying addition */
	void mergeHeap(Vector<Node*>& lhs, Vector<Node*>& rhs);

	/* sets one of the nodes to be the child of the other*/
	Node* mergeNode(Node* lhs, Node* rhs);

	/* resizes a vector by newSize */
	Vector<Node*> resize(Vector<Node*> vec, int num);

	
};

#endif
