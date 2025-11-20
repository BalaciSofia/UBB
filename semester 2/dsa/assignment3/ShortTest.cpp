#include <assert.h>
#include <exception>

#include "ShortTest.h"
#include "IndexedList.h"
#include "ListIterator.h"




void testAll() {
    IndexedList list = IndexedList();
    assert(list.isEmpty());
    list.addToEnd(1);
    assert(list.size() == 1);
    list.addToPosition(0,2);
    assert(list.size() == 2);
    ListIterator it = list.iterator();
    assert(it.valid());
    it.next();
    assert(it.getCurrent() == 1);
    it.first();
    assert(it.getCurrent() == 2);
    assert(list.search(1) == 1);
    assert(list.setElement(1,3) == 1);
    assert(list.getElement(1) == 3);
    assert(list.remove(0) == 2);
    assert(list.size() == 1);
}


void testRemoveBetween() {
    IndexedList list = IndexedList();
    list.addToEnd(1);
    list.addToPosition(0,2);
    list.addToPosition(1,3);
    list.addToEnd(4);
    list.addToEnd(7);

    //if start and end are not valid
    try {
        list.removeBetween(0,9);
        assert(false);
    } catch (std::exception &) {
        assert(true);
    }

    //index 0 1 2 3 4
    //elems 2 3 1 4 7
    //next  1 2 3 4 -1
    list.removeBetween(1,3);

    //elems 2 3 4 7
    assert(list.size() == 4);
    assert(list.getElement(0) == 2);
    assert(list.getElement(1) == 3);
    assert(list.getElement(2) == 4);
    assert(list.getElement(3) == 7);

    //elems 2 7
    list.removeBetween(0,3);
    assert(list.size() == 2);
    assert(list.getElement(0) == 2);
    assert(list.getElement(1) == 7);

}
