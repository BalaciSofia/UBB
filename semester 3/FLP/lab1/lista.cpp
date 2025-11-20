#include "lista.h"
#include <iostream>

using namespace std;


PNod creare_rec(){
  TElem x;
  cout<<"x=";
  cin>>x;
  if (x==0)
    return NULL;
  else{
    PNod p=new Nod();
    p->e=x;
    p->urm=creare_rec();
    return p;
  }
}

Lista creare(){
   Lista l;
   l._prim=creare_rec();
    return l;
}

void tipar_rec(PNod p){
   if (p!=NULL){
     cout<<p->e<<" ";
     tipar_rec(p->urm);
   }
}

void tipar(Lista l){
   tipar_rec(l._prim);
}

void distrug_rec(PNod p){
   if (p!=NULL){
     distrug_rec(p->urm);
     delete p;
   }
}

void distrug(Lista l) {
	//se elibereaza memoria alocata nodurilor listei
    distrug_rec(l._prim);
}


int even_minus_odd_rec(PNod p) {
    if (p == NULL)
        return 0;
    if (p->e % 2 == 0)
        return p->e+even_minus_odd_rec(p->urm);
    else
        return even_minus_odd_rec(p->urm)-p->e;
}

int even_minus_odd(Lista l) {
    return even_minus_odd_rec(l._prim);
}


bool isinB(PNod p, int val) {
    if (p == NULL)
        return false;//end of list
    if (p->e == val)
        return true;//found
    return isinB(p->urm, val);
}

PNod difference_rec(PNod a, PNod b) {
    if (a==NULL)
        return NULL;
    if (isinB(b,a->e)==false) {
        //element is not in b so add it to the new list
        PNod p = new Nod();
        p->e=a->e;
        //next element in a
        p->urm=difference_rec(a->urm,b);
        return p;
    } else {
        return difference_rec(a->urm,b);
    }
}


Lista difference(Lista A, Lista B) {
    Lista rez;
    rez._prim = difference_rec(A._prim, B._prim);
    return rez;
}

