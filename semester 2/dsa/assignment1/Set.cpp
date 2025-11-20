#include "Set.h"
#include "SetITerator.h"

Set::Set() {
	//
	this->cap=1;
	this->length=0;
	this->data=new TElem[this->cap];
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)


bool Set::add(TElem elem) {
	//
	if (this->search(elem)==true)
		return false;
	if (this->size()>=this->cap) {
		this->cap=this->cap*2;
		TElem* newData = new TElem[this->cap];

		for (int i = 0; i < this->length; i++) {
			newData[i] = this->data[i];
		}
		delete[] this->data;
		this->data = newData;
	}
	this->data[this->size()]=elem;
	this->length++;
	return true;
}
// BC: Theta(1), WC: Theta(n), TC: O(n)


bool Set::remove(TElem elem) {
	//
	if (this->search(elem)==false)
		return false;
	int index = -1;
	for (int i = 0; i < this->length; i++) {
		if (this->data[i] == elem) {
			index = i;
			break;
		}
	}
	this->data[index] = this->data[this->size()-1];
	this->data[this->size()-1] = NULL_TELEM;
	this->length--;
	if (this->length <= this->cap / 4 && this->cap > 1) {
		this->cap /= 2;
		TElem* newData = new TElem[this->cap];

		for (int i = 0; i < this->length; i++) {
			newData[i] = this->data[i];
		}
		delete[] this->data;
		this->data = newData;
	}
	return true;
}
// BC: Theta(1), WC: Theta(n), TC: O(n)

bool Set::search(TElem elem) const {
	//
	for (int i=0;i<this->size();i++)
		if (this->data[i]==elem)
			return true;
	return false;
}
// BC: Theta(1), WC: Theta(n), TC: O(n)


int Set::size() const {
	//
	return this->length;
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)


bool Set::isEmpty() const {
	//
	return this->length==0;
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)


Set::~Set() {
	//
	delete [] this->data;
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)


SetIterator Set::iterator() const {
	return SetIterator(*this);
}


