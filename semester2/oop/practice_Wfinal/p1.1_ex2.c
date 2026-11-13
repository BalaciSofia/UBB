// c)
#include <iostream>

class B {
public:
    B() {}
    B(const B& b) { std::cout << "copy "; }
    virtual void f() { std::cout << "B.f "; }
    void g(B b) { std::cout << "B.g "; }
    virtual ~B() { std::cout << "~B "; }
};
class D : public B {
public:
    D() {}
    void f() {
        B::f();
        std::cout << "D.f ";
    }
    void g(D d) {
        B::g(d);
        std::cout << "D.g ";
    }
};
int main()
{
    B* b = new B{};
    B* d = new D{};

    d->f();         // Dynamic call
    d->g(*b);       // Sliced copy passed by value

    delete b;
    delete d;

    return 0;
}

