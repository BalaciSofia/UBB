#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
	std::pair<TKey, TValue*>* sortedArray;
	int* lengths;
	int currentArray;
	int currentIndex;
	int length;

	bool comp(pair<TKey, TValue*> a, pair<TKey, TValue*> b);

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

