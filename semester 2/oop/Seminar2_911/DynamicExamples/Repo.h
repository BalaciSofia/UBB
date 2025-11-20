#pragma once
#include "Planet.h"

typedef void* TElem;

//typedef struct {
//	TElem *elements;
//	int length;
//	int capacity;
//}DynamicArray;
//
//typedef struct {
//	DynamicArray planets;
//}Repo;



//typedef struct {
//	DynamicArray planets;
//}UndoOperationsStack;
//typedef struct {
//	DynamicArray planets;
//}RedoOperationsStack;

// TElem* get(Repo *r, int idx);

typedef struct {
	TElem *elements;
	int length;
	int capacity;
}Repo;

Repo* createRepo();
void resize(Repo *r);
void destroyRepo(Repo *r);
void addPlanet(Repo *repo, Planet *p);