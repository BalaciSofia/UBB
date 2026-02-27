// d)
#include <iostream>
class A {
private:
    int* x;

public:
    A(int _x = 0) {
        x = new int{_x};
    }

    A(const A& a) {
        x = new int{*a.x};
    }

    int get() { return *x; }

    void set(int _x) { *x = _x; }

    ~A() {
	    if(x==nullptr)
        	delete x;
    }
};

int main()
{
    A a1, a2;
    a1.set(8);

    A a3;
    a3 = a1;  // uses default assignment operator (shallow copy!)

    A a4 = a1;  // uses copy constructor (deep copy)

    a1.set(5);

    std::cout << a1.get() << " ";
    std::cout << a2.get() << " ";
    std::cout << a3.get() << " ";
    std::cout << a4.get() << " ";

    system("pause");
    return 0;
}

