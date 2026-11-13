#include "ShortTest.h"
#include "Bag.h"
#include "BagIterator.h"
#include "assert.h"
#include <exception>
#include <iostream>
#include <ostream>
using namespace std;

void testAll() { 
	Bag b;
	assert(b.isEmpty() == true);
	assert(b.size() == 0); 
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.size() == 7);
	assert(b.search(10) == true);
	assert(b.search(16) == false);
 	assert(b.nrOccurrences(1) == 2);
 	assert(b.nrOccurrences(7) == 1);
 	assert(b.remove(1) == true);
 	assert(b.remove(6) == false);
 	assert(b.size() == 6);
 	assert(b.nrOccurrences(1) == 1);
 	BagIterator it = b.iterator();
	it.first();
	while (it.valid()) {
		TElem e = it.getCurrent();
		it.next();
	}
}

void testBagRemove() {
	Bag b;
	BagIterator it = b.iterator();
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	it.first();
	it.next();
	assert(it.getCurrent() == 1);
	assert(it.remove() == 1);
	assert(it.valid() == true);
	assert(it.getCurrent() == 10);
	it.next();
	it.next();
	it.next();
	assert(it.getCurrent() == -3 );
	assert(it.remove() == -3);
	assert(it.valid() == false);
	try {
		it.remove();
		assert(false);
	}catch (std::exception&) {
		assert(true);
	}
	assert(b.size() == 5);
	it.first();
	assert(it.remove() == 5);
	assert(it.valid() == true);
	assert(it.getCurrent() == 10);
}

void test() {
	Bag b;
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(1);
	b.add(11);
	b.add(-3);
	b.add(5);
	b.add(1);
	BagIterator it = b.iterator();
	it.next();
	it.remove();
	cout << it.getCurrent() << endl;
	it.next();
	cout << it.getCurrent() << endl;
	it.next();
	cout<< it.getCurrent() << endl;
}