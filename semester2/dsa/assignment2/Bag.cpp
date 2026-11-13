#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//TODO - Implementation
	this->head = NULL;
	this->tail = NULL;
	this->length = 0;
}


void Bag::add(TElem elem) {
	//TODO - Implementation
	Node *current = this->head;

	while (current != NULL) {
		if (current->elem == elem) {
			current->frequency = current->frequency + 1;
			this->length++;
			return;
		}
		current=current->next;
	}

	Node *newNode = new Node();
	newNode->elem = elem;
	newNode->frequency = 1;
	newNode->next =NULL;
	newNode->prev = this->tail;
	if (this->head == NULL) {
		this->head=newNode;
		this->tail=newNode;
	}
	else {
		this->tail->next = newNode;
		this->tail = newNode;
	}
	this->length++;
}
//Bc=theta(1) Wc=theta(n) Tc=O(n)

bool Bag::remove(TElem elem) {
	//TODO - Implementation
	Node *current = this->head;
	while (current != NULL) {
		if (current->elem == elem) {
			current->frequency = current->frequency - 1;
			if (current->frequency == 0) {
				if (current == head) {
					head = head->next;
					if (head != NULL) head->prev = NULL;
					else tail = NULL;
				} else if (current == tail) {
					tail = tail->prev;
					if (tail != NULL) tail->next = NULL;
					else head = NULL;
				} else {
					current->prev->next = current->next;
					current->next->prev = current->prev;
				}
				delete current;
			}
			this->length--;
			return true;
		}
		current = current->next;
	}
	return false;
}
//Bc=theta(1) Wc=theta(n) Tc=O(n)

bool Bag::search(TElem elem) const {
	//TODO - Implementation
	Node *current = this->head;
	while (current != NULL) {
		if (current->elem == elem) {
			return true;
		}
		current=current->next;
	}
	return false; 
}
//Bc=theta(1) Wc=theta(n) Tc=O(n)

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	Node *current = this->head;
	while (current != NULL) {
		if (current->elem == elem) {
			return current->frequency;
		}
		current=current->next;
	}
	return 0;
}
//Bc=theta(1) Wc=theta(n) Tc=O(n)


int Bag::size() const {
	//TODO - Implementation
	return this->length;
}
//Bc=theta(1) Wc=theta(1) Tc=theta(1)

bool Bag::isEmpty() const {
	//TODO - Implementation
	return this->length==0;
}
//Bc=theta(1) Wc=theta(1) Tc=theta(1)

BagIterator Bag::iterator(){
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - Implementation
	Node *aux = this->head;
	while (this->head != NULL) {
		aux=this->head;
		this->head = this->head->next;
		delete aux;
	}
	this->tail = NULL;
}
//Bc=theta(n) Wc=theta(n) Tc=theta(n)
