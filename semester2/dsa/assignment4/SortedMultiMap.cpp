#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

int SortedMultiMap::hash1(TKey key) const {
	return key % this->m;
}

int SortedMultiMap::hash2(TKey key) const {
	return 1 + (key %(this->m-1));
}

int SortedMultiMap::findSlot(TKey key) const {
	int pos = hash1(key);
	while (this->table[pos].key != key && this->table[pos].occupied == true) {
		pos = (pos + hash2(key)) % (this->m);
		if (pos == hash1(key)) break;
	}
	return pos;
}

int SortedMultiMap::next_prime(int x) const {
	if (x%2 == 0) x++;
	while (true) {
		bool prime = true;
		for (int i = 3; i*i <= x; i += 2) {
            if (x%i == 0) {
                prime = false;
                break;
            }
        }
		if (prime) return x;
		x += 2;
	}
}

void SortedMultiMap::resize() {
    //TODO - Implementation
    int old_m = this->m;
    this->m = next_prime(this->m*2);
    HashNode* old_table = this->table;
    this->table = new HashNode[this->m];
    for (int i = 0; i < this->m; i++)
        this->table[i].occupied = false;
	this->key_count = 0;
    this->length = 0;
    for (int i = 0; i < old_m; i++) {
        if (old_table[i].occupied) {
            for (int j = 0; j < old_table[i].length; j++) {
                this->add(old_table[i].key, old_table[i].values[j]);
            }
            delete[] old_table[i].values;
        }
    }
    delete[] old_table;
}

SortedMultiMap::SortedMultiMap(Relation r) {
	//TODO - Implementation
	this->relation = r;
	this->m = 17;
	this->table = new HashNode[this->m];
	for (int i = 0; i < this->m; i++)
		this->table[i].occupied = false;
	this->length = 0;
}

void SortedMultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	double loadFactor = (double)this->length / this->m;
	if (loadFactor > 0.75) this->resize();
	int pos = findSlot(c);
	this->table[pos].occupied = true;
	this->table[pos].key = c;
	this->length++;
	if (this->table[pos].length == 0) {
		this->table[pos].values = new TValue[this->table[pos].capacity];
		this->table[pos].values[0] = v;
		this->table[pos].length = 1;
		this->key_count++;
		return;
	}
	if (this->table[pos].length == this->table[pos].capacity) {
		this->table[pos].capacity *= 2;
		TValue* newVals = new TValue[this->table[pos].capacity];
		for (int i=0; i < this->table[pos].capacity; i++)
			newVals[i] = this->table[pos].values[i];
		delete[] this->table[pos].values;
		this->table[pos].values = newVals;
	}
	this->table[pos].values[this->table[pos].length++] = v;
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	// TODO - Implementation
	int pos = findSlot(c);
	if (this->table[pos].key != c) return vector<TValue>();
	vector<TValue> vals;
	for (int i=0; i < this->table[pos].length; i++)
		vals.push_back(this->table[pos].values[i]);
	return vals;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
    int pos = findSlot(c);
	if (this->table[pos].key != c) return false;
	for (int i=0; i<this->table[pos].length; i++)
		if (this->table[pos].values[i] == v) {
			if (i == this->table[pos].length-1) {
                this->table[pos].length--;
				this->length--;
				if (this->table[pos].length == 0) {
					delete [] this->table[pos].values;
					this->table[pos].occupied = false;
					this->key_count--;
				}
                return true;
            }
			while (this->table[pos].length && this->table[pos].values[i] == v) {
				this->table[pos].values[i] = this->table[pos].values[this->table[pos].length-1];
				this->table[pos].length--;
			}
			this->length--;
			if (this->table[pos].length == 0) {
                delete [] this->table[pos].values;
                this->table[pos].occupied = false;
				this->key_count--;
            }
			return true;
		}
	return false;
}

int SortedMultiMap::size() const {
	//TODO - Implementation
	return this->length;
}

bool SortedMultiMap::isEmpty() const {
	//TODO - Implementation
	return this->length == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	//TODO - Implementation
	for (int i = 0; i < this->m; i++) {
        if (this->table[i].occupied) {
            delete[] this->table[i].values;
        }
    }
	delete [] this->table;
}
