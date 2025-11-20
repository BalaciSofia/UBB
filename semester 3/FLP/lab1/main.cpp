#include "lista.h"
#include <iostream>

int main()
{
   Lista l,l1,l2;
   l=creare();
   tipar(l);
   std::cout<<"a:";
   std::cout<<std::endl<<"even-odd="<<even_minus_odd(l)<<std::endl;
   l1=creare();//1 2 3 4
   l2=creare();//2 4 5
   tipar(l1);
   std::cout<<std::endl;
   tipar(l2);
   std::cout<<"b:"<<std::endl;
   std::cout<<std::endl<<"difference:";
   tipar(difference(l1,l2));
}
