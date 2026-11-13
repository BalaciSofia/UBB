#pragma once
#include "Planet.h"
typedef struct {
	Planet planets[100];
	int length;
}Repo;

Repo createRepo();
void addPlanet(Repo *repo, Planet p);