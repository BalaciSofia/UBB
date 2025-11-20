#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

using namespace std;

int main(){
    testAll();
    testAllExtended();
    testRemoveBetween();
    cout<<"Test removeBetween passed!"<<endl;
    cout<<"Finished LI Tests!"<<endl;
}