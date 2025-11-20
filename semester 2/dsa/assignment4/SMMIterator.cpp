#include "SMMIterator.h"

#include <algorithm>

#include "SortedMultiMap.h"

bool SMMIterator::comp(std::pair<TKey, TValue*> a, std::pair<TKey, TValue*> b) {
	//TODO - Implementation
	//compare the keys of the two pairs using the relation
	return this->map.relation(a.first, b.first);
}

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	//TODO - Implementation
	//create a sorted array of <key, dynamic array of values> pairs
	this->length = d.key_count;
	this->sortedArray = new std::pair<TKey, TValue*>[this->length];
	this->lengths = new int[this->length];
	int index = 0;
	for (int i = 0; i < d.m; i++) {
		if (d.table[i].occupied == true) {
			this->sortedArray[index].first = d.table[i].key;
			this->sortedArray[index].second = d.table[i].values;
			this->lengths[index] = d.table[i].length;
			index++;
		}
	}
	this->currentIndex = 0;
	this->currentArray = 0;
	//sort the array using the relation
	std::sort(this->sortedArray, this->sortedArray + this->length,
		[this](std::pair<TKey, TValue*> a, std::pair<TKey, TValue*> b) {
			return this->comp(a, b);
		});
}

void SMMIterator::first(){
	//TODO - Implementation
	this->currentIndex = 0;
	this->currentArray = 0;
}

void SMMIterator::next() {
	// TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	this->currentIndex++;
	if (this->currentIndex >= this->lengths[this->currentArray]) {
		this->currentArray++;
		this->currentIndex = 0;
	}
}


bool SMMIterator::valid() const{
	//TODO - Implementation
	return this->currentArray < this->length && this->currentIndex < this->lengths[this->currentArray];
}

TElem SMMIterator::getCurrent() const{
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	return std::make_pair(this->sortedArray[this->currentArray].first, this->sortedArray[this->currentArray].second[this->currentIndex]);
}


