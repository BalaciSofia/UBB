#include "SetIterator.h"
#include "Set.h"

//-
#include <exception>
using namespace::std;
//-

SetIterator::SetIterator(const Set& s) : set(s)
{
	//
	this->index = 0;
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)

void SetIterator::first() {
	//
	this->index = 0;
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)

void SetIterator::next() {
	//
	if (this->index >= set.size())
        throw exception();
	this->index++;
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)

TElem SetIterator::getCurrent()
{
	//
	if (this->index >= set.size())
		throw exception();
	return this->set.data[this->index];
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)

bool SetIterator::valid() const {
	//
	return this->index < this->set.size();
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)

void SetIterator::jumpForword(int k) {
	//throw exception if iterator is invalid
	if (this->index >= set.size() || k <=0)
		throw exception();
	//check if there are more k elems in set
	if (this->index+k >= this->set.size())
		this->index=set.size();
	//move current element  steps forward
	this->index+=k;

	// int now=this->index;
	// int current=this->set.data[now];
	// for (int i=this->index; i<now+k; i++)
	// 	this->set.data[i]=this->set.data[i+1];
	// set.data[now+k]=current;
	// for (int i=now+k+1; i<set.size(); i++)
	// 	this->set.data[i]=this->set.data[i+1];
}
// BC: Theta(1), WC: Theta(1), TC: Theta(1)
