
#pragma once

typedef struct{
  char type[20];
  char address[50];
  int surface;
  int price;
}Estate;

Estate createEstate(char *type, char *address, int surface, int price);
Estate * copyEstate(Estate* estate);
void run_test_domain();