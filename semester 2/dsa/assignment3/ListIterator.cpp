#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(const IndexedList& list) : list(list){
   //TODO - Implementation
    this->current = this->list.head;
}

void ListIterator::first(){
    //TODO - Implementation
    this->current = this->list.head;
}

void ListIterator::next(){
    //TODO - Implementation
    if (!this->valid()) {
        throw std::exception();
    }
    this->current = this->list.next[this->current];
}

bool ListIterator::valid() const{
    //TODO - Implementation
    //iterator is valid till there is a next element(current != -1)
    return this->current != -1;
}

TElem ListIterator::getCurrent() const{
   //TODO - Implementation
    if (!this->valid()) {
        throw std::exception();
    }
    return this->list.elements[this->current];
}