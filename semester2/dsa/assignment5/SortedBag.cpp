#include "SortedBag.h"

#include <iostream>
#include <ostream>

#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->root = nullptr;
	this->relation = r;
}


void SortedBag::add(TComp e) {
	//TODO - Implementation
	//initialize new node
	bstNode* newNode = new bstNode();
	newNode->info = e;
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->parent = nullptr;
	//if no root initialize root
	if (root == nullptr) {
		root = newNode;
		return;
	}
	//find place for the new node
	bstNode* current = root;
	while (true) {
		//if the new node is smaller or equal to the current node, go left
		if (this->relation(e,current->info)) {
			//if the left child is null, insert the new node
			if (!current->left) {
				//assign  the new node as the left child
				current->left = newNode;
				//set the parent of the new node
				newNode->parent = current;
				return;
			}
			else {
				//if the left child is not null, go to the left child
				current = current->left;
			}
		}
		//if the new node is greater than the current node, go right
		else {
			if (!current->right) {
				//if the right child is null, insert the new node
				current->right = newNode;
				newNode->parent = current;
				return;
			}
			else {
				//if the right child is not null, go to the right child
				current = current->right;
			}
		}
	}
}
//bc=Theta(1)-when the root is null and we add the first element
//wc=Theta(n)-when we add the element at the end of the tree(when the tree is a linked list)
//tc=O(n)


bool SortedBag::remove(TComp e) {
	//TODO - Implementation
    bstNode* current = root;
    while (current) {
        if (current->info == e) {
            //node found
            if (current->left == nullptr && current->right == nullptr) {
                //case 1: no child
                if (current->parent) {//if it has a parent
                	//if left the current is the left child of the parent
                    if (current->parent->left == current) {
                        current->parent->left = nullptr;
                    } else {
                        current->parent->right = nullptr;
                    }
                } else {
                    root = nullptr; //if it s the root node
                }
                delete current;
            } else if (current->left == nullptr || current->right == nullptr) {
                //case 2: one child
            	bstNode* child;
            	//initialize child with the non-null child
            	if (current->left) {
            		child = current->left;
            	} else {
            		child = current->right;
            	}
            	if (current->parent) {//if it has a parent
                    if (current->parent->left == current) {//if the current is the left child of the parent
                        current->parent->left = child; //assign child to the left of parent
                    } else {//if the current is the right child of the parent
                        current->parent->right = child; //assign child to the right of parent
                    }
                } else {
                    root = child; // if it s the root
                }
                child->parent = current->parent;//set the parent of the child
                delete current;
            } else {
                //case 3: two children
            	//find the in-order successor (smallest node in the right subtree)
                bstNode* successor = current->right;//start with the right child
                while (successor->left) {//traverse to the leftmost node in the right subtree
                    successor = successor->left;
                }
                current->info = successor->info; //copy successor's value
                //remove the successor node
                if (successor->parent->left == successor) {//if the succesor is the left child of its parent
                    successor->parent->left = successor->right;//assign the right child of the successor
                } else {//if the successor is the right child of its parent
                    successor->parent->right = successor->right;//assign the right child of the successor
                }
            	//if the successor has a right child, set its parent to the successor's parent
                if (successor->right) {
                    successor->right->parent = successor->parent;
                }
                delete successor;
            }
            return true;
        } else if (relation(e, current->info)) {//if the element is smaller than the current node
            current = current->left;
        } else {//if the element is greater than the current node
            current = current->right;
        }
    }
    return false;
}
//bc=Theta(1)-when the root is null and have nothing to remove
//wc=Theta(n)-when the tree is a linked list and we remove the last element
//tc=O(n)

bool SortedBag::search(TComp elem) const {
	//TODO - Implementation
	bstNode* current = this->root;
	while (current) {
		if (current->info == elem) {
			return true;
		}
		else if (relation(current->info,elem)) {//if the current node is bigger than the element we are looking for
			current = current->right;
		}
		else {//if the current node is smaller than the element we are looking for
			current = current->left;
		}
	}
	return false;
}
//bc=Theta(1)-when the element is the root
//wc=Theta(n) because the height of the tree can be between log n and n
//tc=O(n)


int SortedBag::nrOccurrences(TComp elem) const {
	//TODO - Implementation
	bstNode* current = this->root;
	int nrOccurrences = 0;
	bstNode **stack = new bstNode*[this->size()]; //stack for traversal
	int stackSize = 0;

	//in-order traversal
	while (stackSize > 0 || current != nullptr) {
		while (current != nullptr) {
			stack[stackSize++] = current; //push current
			current = current->left;
		}
		//pop from stack
		current = stack[--stackSize];

		if (current ->info == elem) {
			nrOccurrences++;
		}
		//visit right subtree
		current = current->right;
	}
	delete[] stack;
	return nrOccurrences;
}
//bc=Theta(1)-when the root is null and we have nothing to search for
//wc=Theta(n)-when the tree is a linked list
//tc=O(n)



int SortedBag::size() const {
	//TODO - Implementation
	int count = 0;
	int capacity = 10;

	bstNode** stack = new bstNode*[capacity];//stack for traversal
	int top = 0;

	bstNode* current = this->root;

	while (current || top > 0) {
		//go to leftmost node
		while (current) {
			//resize stack if needed
			if (top >= capacity) {
				int newCapacity = capacity * 2;
				bstNode** newStack = new bstNode*[newCapacity];
				for (int i = 0; i < top; ++i) {
					newStack[i] = stack[i];
				}
				delete[] stack;
				stack = newStack;
				capacity = newCapacity;
			}
			stack[top++] = current;//push current
			current = current->left;
		}

		current = stack[--top];//pop from stack
		count++;//increment count for each visited node
		current = current->right;
	}
	delete[] stack;
	return count;
}
//bc=Theta(1)-when the root is null
//wc=Theta(n)-when the tree is a linked list
//tc=O(n)


bool SortedBag::isEmpty() const {
	//TODO - Implementation
	return root == nullptr;
}
//bc=wc=tc=Theta(1)


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	//TODO - Implementation
	//post-order traversal to delete all nodes
	if (root == nullptr) {
		return;
	}
	bstNode** stack = new bstNode*[this->size()];
	int stackSize = 0;

	bstNode* current = root;
	bstNode* lastVisited = nullptr;

	while (stackSize > 0 || current != nullptr) {
		if (current != nullptr) {
			stack[stackSize++] = current; //push current
			current = current->left;     //go left child
		} else {
			bstNode* node = stack[stackSize - 1];
			if (node->right != nullptr && lastVisited != node->right) {
				current = node->right; //go right child
			} else {
				//visit node
				delete node;
				lastVisited = stack[--stackSize]; //pop from stack
			}
		}
	}

	delete[] stack;
}
//bc=wc=tc=Theta(n) - we traverse the whole tree to delete all nodes



///lab---------------------------------------------------------------------------

//counts and returns the number of distinct elements in the bag
int SortedBag::distinctCount() const {
	if (this->root == nullptr) {
		return 0;
	}
	int count = 0;
	TComp lastValue = NULL_TCOMP; //contains the last distinct value found

	bstNode** stack = new bstNode*[this->size()];
	int stackSize = 0;

	bstNode* current = this->root;
	while (stackSize > 0 || current != nullptr) {
		while (current != nullptr) {
			stack[stackSize++] = current;
			current = current->left;
		}
		current = stack[--stackSize];
		//if the current value is distinct
		if (current->info != lastValue) {
			count++;
			lastValue = current->info;
		}
		current = current->right;
	}
	delete[] stack;
	return count;
}