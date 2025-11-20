#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

IndexedList::IndexedList() {
	//TODO - Implementation
    this->cap = 5; //initial capacity
    this->elements = new TElem[this->cap];//allocate memory for the array of elements
    this->next = new int[this->cap];//allocate memory for the array of next
    this->head = -1;
    this->firstEmpty=0;//the first empty position is 0
    for (int i = 0; i < this->cap - 1; i++) {
        this->next[i] = i + 1;//for each position i, the next element is on position i+1
    }
    this->next[this->cap - 1] = -1;//last element has no next
}
//Bc=Wc=Tc=Theta(n)

int IndexedList::size() const {
    //TODO - Implementation
    int c = 0;
    int i = this->head;
    while (i != -1) {//while next exists
        c++;
        i = this->next[i];
    }
    return c;
}
//Bc=Wc=Tc=Theta(n)


bool IndexedList::isEmpty() const {
    //TODO - Implementation
	return this->head == -1;
}
//Bc=Wc=Tc=Theta(1)

TElem IndexedList::getElement(int pos) const {
    //TODO - Implementation
    if (pos < 0 || pos >= this->size()) {
        throw std::exception();
    }
    int curr = this->head;
    for (int i = 0; i < pos; i++) {
        curr = this->next[curr];
    }
	return this->elements[curr];
}
//Bc=Theta(1)-when the pos is not valid or the pos is 0
//Wc=Theta(n)-when the pos is the last element
//Tc=O(n)

TElem IndexedList::setElement(int pos, TElem e) {
    //TODO - Implementation
    if (pos < 0 || pos >= this->size()) {
        throw std::exception();
    }
    int curr = this->head;
    for (int i = 0; i < pos; i++) {
        curr = this->next[curr];
    }
    TElem old = this->elements[curr];
    this->elements[curr] = e;
	return old;
}
//Bc=Theta(1)-when the pos is not valid or the pos is 0
//Wc=Theta(n)-when the pos is the last element
//Tc=O(n)

void IndexedList::addToEnd(TElem e) {
    //TODO - Implementation
    if (this->firstEmpty == -1) {
        //if there are no empty positions left, we need to resize
        TElem *newElements = new TElem[this->cap * 2];
        int *newNext = new int[this->cap * 2];
        for (int i = 0; i < this->cap; i++) {
            newElements[i] = this->elements[i];
            newNext[i] = this->next[i];
        }
        for (int i = this->cap; i < this->cap * 2 - 1; i++) {
            newNext[i] = i + 1;
        }
        newNext[this->cap * 2 - 1] = -1;
        delete[] this->elements;
        delete[] this->next;
        this->elements = newElements;
        this->next = newNext;
        this->firstEmpty = this->cap;
        this->cap *= 2;
    }
    //add the element to the end of the list
    int newPos = this->firstEmpty;//new position is the first empty position
    this->elements[newPos] = e;//the value of the element on position newPos is e
    this->firstEmpty = this->next[this->firstEmpty];//the first empty position is the next of the rest empty positions
    this->next[newPos] = -1;//bc it is the last element, the next of the last element is -1
    if ( this->head == -1 ) {
        //if there is no element in the list, we set the head to be the new added element(position)
        this->head = newPos;
    }else {
        int curr = this->head;
        while (this->next[curr] != -1) {
            //we go to the last element
            curr = this->next[curr];
        }
        this->next[curr] = newPos;//set its next to be the new added elements position
    }
}
//Bc=Theta(1)-when the list is empty so the added element is the first(head)
//Wc=Theta(n)-when the list is full and we need to resize
//Tc=O(n)

void IndexedList::addToPosition(int pos, TElem e) {
    //TODO - Implementation
    //if the position is not valid
    if (pos < 0 || pos > this->size()) {
        throw std::exception();
    }
    if (this->firstEmpty == -1) {
        //if there are no empty positions left, we need to resize
        TElem *newElements = new TElem[this->cap * 2];
        int *newNext = new int[this->cap * 2];
        for (int i = 0; i < this->cap; i++) {
            newElements[i] = this->elements[i];
            newNext[i] = this->next[i];
        }
        for (int i = this->cap; i < this->cap * 2 - 1; i++) {
            newNext[i] = i + 1;
        }
        newNext[this->cap * 2 - 1] = -1;
        delete[] this->elements;
        delete[] this->next;
        this->elements = newElements;
        this->next = newNext;
        this->firstEmpty = this->cap;
        this->cap *= 2;
    }
    int newPos = this->firstEmpty;//new position is the first empty position
    this->elements[newPos] = e;//the value of the element on position newPos is e
    this->firstEmpty = this->next[this->firstEmpty];//the first empty position is the next of the rest empty positions
    if (pos == 0) {
        //if the pos is 0 it means that we need to add the element at the beginning of the list
        //aka we have a new head
        this->next[newPos] = this->head;//the next of the new element is the old head
        this->head = newPos;//the new head is the new element
    }else {
        int curr = this->head;
        for (int i = 0; i < pos-1; i++) {
            //go to the position before the one we want to add the element
            curr = this->next[curr];
        }
        this->next[newPos] = this->next[curr];//the next of the new element is the next of the current element
        this->next[curr] = newPos;//the next of the current element is the new element
    }
}
//Bc=Theta(1)-when the position is 0(head)
//Wc=Theta(n)-when the list is full and we need to resize
//Tc=O(n)

TElem IndexedList::remove(int pos) {
    //TODO - Implementation
    //validate position
    if (pos < 0 || pos >= this->size()) {
        throw std::exception();
    }
    int curr = this->head;
    int prev = -1;//the previous element position
    //go to the position we want to remove
    for (int i = 0; i < pos; i++) {
        prev = curr;
        curr = this->next[curr];
    }
    if (prev == -1) {
        //if the previous element is -1 it means that we are removing the head
        this->head = this->next[curr];//the new head is the next of the current element
    }else {
        //otherwise we need to set the next of the previous element to be the next of the current element
        this->next[prev] = this->next[curr];
    }
    TElem removed = this->elements[curr];//this is the removed element
    this->next[curr] = this->firstEmpty;//the next of the removed element is the first empty position
    this->firstEmpty = curr;//the first empty position is the removed element
    return removed;//return the removed element
}
//Bc=Theta(1)-when the pos to be removed is 0(head)
//Wc=Theta(n)-when the pos to be removed is the last element
//Tc=O(n)

int IndexedList::search(TElem e) const{
    //TODO - Implementation
    int current = this->head;
    int pos = 0;
    while (current != -1) {
        if (this->elements[current] == e) {
            return pos;
        }
        current = this->next[current];
        pos++;
    }
    return -1;
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
	//TODO - Implementation
    //free the arrays
    delete[] this->elements;
    delete[] this->next;
}


//in lab

void IndexedList::removeBetween(int start, int end) {
    if (start < 0 || end >= this->size() || start > end) {
        throw std::exception(); // Validate positions
    }
    //removes all elements between two given positions
    int curr = this->head;
    int prev=-1;
    //iteram pana la poz start+1;
    for (int i=0; i < start+1; i++) {
        prev = curr;
        curr = this->next[curr];
    }
    //curr acuma il are pe urmatorul dupa start trebe sa stergem pana la end
    for (int i = start+1; i < end ; i++) {
        int toRemove = curr;//salvam ce i de sters
        curr = this->next[curr]; //mergem la urm
        this->next[toRemove] = this->firstEmpty; //punem in next-ul lui pe primul liber
        this->firstEmpty = toRemove;//primul liber e ce tocmai am sters
    }
    this->next[prev] = curr;//unim capetele
}
