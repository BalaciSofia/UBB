#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	 Bag& bag;
	//TODO  - Representation
	Bag::Node *current;
	int frequency;

	BagIterator(Bag& c);
public:
	void first();
	void next();
	TElem getCurrent();
	bool valid();
	TElem remove();
};
