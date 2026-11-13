#include "domain.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Estate createEstate(char *type,char *address,int surface, int price){
    /*
     *creates an instance of an estate
     *param1:type=house/apartment/penthouse
     *param2:address(unique)
     *param3:surface of estate
     *param4:price of estate
     */
  Estate estate;
  strcpy(estate.type,type);
  strcpy(estate.address,address);
  estate.surface=surface;
  estate.price=price;
  return estate;
  }

Estate* copyEstate(Estate* estate) {
    /*
     *creates a deep copy of an estate
     *param:estate we want to copy
     *returns: the copy
     */
    Estate* new_estate = malloc(sizeof(Estate));
    strcpy(new_estate->address, estate->address);
    strcpy(new_estate->type, estate->type);
    new_estate->price = estate->price;
    new_estate->surface = estate->surface;
    return new_estate;
}

//tests--------------------------------------------------------------------------------------------

void test_createEstate() {
    Estate e = createEstate("house", "Str Soarelui", 100, 50000);
    assert(strcmp(e.type, "house") == 0);
    assert(strcmp(e.address, "Str Soarelui") == 0);
    assert(e.surface == 100);
    assert(e.price == 50000);
}

void test_copyEstate() {
    Estate e1 = createEstate("apartment", "Str Soarelui", 80, 75000);
    Estate *e2 = copyEstate(&e1);
    assert(e2 != NULL);
    assert(strcmp(e2->type, "apartment") == 0);
    assert(strcmp(e2->address, "Str Soarelui") == 0);
    assert(e2->surface == 80);
    assert(e2->price == 75000);
    free(e2);
}

void run_test_domain() {
    test_createEstate();
    test_copyEstate();
}