#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	const Set& set;
	int index;
	SetIterator(const Set& s);

	//

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
	void jumpForword(int k);
};


