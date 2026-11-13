#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation
	int bagsize= bag.size();
	//initialize the array with the in order traversal of the tree
	this->array= new TElem[bagsize];
	//use a stack to fill the array with the in order traversal
	SortedBag::bstNode ** stack = new SortedBag::bstNode*[bagsize];
	int stackSize = 0;

	SortedBag::bstNode* current = bag.root;
	int index = 0;

	//in-order traversal
	while (stackSize > 0 || current != nullptr) {
		while (current != nullptr) {
			stack[stackSize++] = current; // push current
			current = current->left;
		}
		current = stack[--stackSize];//pop from stack

		this->array[index++] = current->info;//add node to array

		current = current->right;//right subtree
	}
	this->length = index;//length of the array is the number of elements in the bag
	this->index = 0;//iterator index starts at 0
	delete[] stack;
}
//bc=wc=tc=Theta(n) - we traverse the whole tree to fill the array

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (!this->valid()) {
		throw exception();
	}
	return this->array[this->index];
}
//bc=wc=tc=Theta(1)

bool SortedBagIterator::valid() {
	//TODO - Implementation
	return (this->index >= 0 && this->index < this->length);
}
//bc=wc=tc=Theta(1)

void SortedBagIterator::next() {
	//TODO - Implementation
	if (!this->valid()) {
		throw exception();
	}
	this->index++;
}
//bc=wc=tc=Theta(1)


void SortedBagIterator::first() {
	//TODO - Implementation
	this->index = 0;
}
//bc=wc=tc=Theta(1)


