
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

template <typename T>
class Adder{
	private:
		std::vector<T> elements;
	public:
		Adder(T elem){
			this->elements.push_back(elem);
		}
		Adder &operator=(const Adder &other){
			if(this!=&other)
				this->elements=other.elements;
			return *this;
		}
		Adder operator+(T elem){
			Adder copy=*this;
			copy.elements.push_back(elem);
			return copy;
		}
		Adder & operator++(){
			this->elements.push_back(elements[elements.size()-1]);
		return *this;
		}
		Adder & operator--(){
			if(this->elements.size()<=0)
				throw std::runtime_error("no more values");
			this->elements.erase(this->elements.begin()+this->elements.size()-1);
		return *this;
		}

		T sum(){
			T s=0;
			for (auto e:elements){
				s=s+e;
			}
			return s;
		}

};


void function2() {
    Adder<int> add{5};         // build a new Adder, with initial value 5
    add = add + 5 + 2;         // add values 5 and 2
    ++add;                     // adds the last added value (2) again
    add = add + 8;             // add value 8
    std::cout << add.sum() << "\n"; // print sum, so far: 22 (5+5+2+2+8)

    --add;                     // eliminate last added value
    std::cout << add.sum() << "\n"; // print modified sum: 14 (5+5+2+2)

    --(--add);                 // eliminate the two previously added values
    std::cout << add.sum() << "\n"; // print modified sum: 10 (5+5)

    try {
       --(--(--add));         // eliminate 5, then 5, then fail (no more values)
    } catch (std::runtime_error& ex) {
	    std::cout << ex.what();     // prints "No more values!"
    }
}



int main(){
	function2();
	return 0;
}
