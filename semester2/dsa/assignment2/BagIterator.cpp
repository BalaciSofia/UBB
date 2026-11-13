#include <exception>
#include "BagIterator.h"

#include <utility>

#include "Bag.h"

using namespace std;


BagIterator::BagIterator(Bag& c): bag(c)
{
	//TODO - Implementation
	this->current=bag.head;
	this->frequency=0;
}

void BagIterator::first() {
	//TODO - Implementation
	this->current=this->bag.head;
	this->frequency = 0;
}
//Bc=theta(1) Wc=theta(1) Tc=theta(1)

void BagIterator::next() {
	//TODO - Implementation
	if (!valid())
		throw exception();
	if (this->frequency < this->current->frequency - 1) {
		this->frequency++;
	} else {
		this->current = this->current->next;
		this->frequency = 0;
	}
}
//Bc=theta(1) Wc=theta(1) Tc=theta(1)

bool BagIterator::valid()
{
	//TODO - Implementation
	return this->current!=NULL;
}
//Bc=theta(1) Wc=theta(1) Tc=theta(1)

TElem BagIterator::getCurrent()
{
	//TODO - Implementation
	if (!valid())
		throw exception();
	return this->current->elem;
}
//Bc=theta(1) Wc=theta(1) Tc=theta(1)

////lab
TElem BagIterator::remove() {
	if (!valid())
		throw exception();
	Bag::Node *n = this->current;
	TElem t = n->elem;
	if (this->current==bag.tail) {
		this->current->prev->next = NULL;
		bag.tail=this->current->prev;
		this->frequency = 0;
		delete n;
		this->current=NULL;
	}
	else {
		if (this->current==bag.head) {
			this->current=this->current->next;
			bag.head=bag.head->next;
			bag.head->prev=NULL;
			this->frequency = 0;
			delete n;
		}
		else {
			this->current->prev->next=this->current->next;
			this->current->next->prev=this->current->prev;
			this->current=this->current->next;
			this->frequency = 0;
			delete n;
		}
	}
	bag.length--;
	return t;
}
//Bc=theta(1) Wc=theta(1) Tc=theta(1)
