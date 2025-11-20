#pragma once
#include <string.h>
#include <stdlib.h>

typedef struct {
	char *name;
	char *type;
	float distance;
}Planet;

Planet* createPlanet(char *name, char *type, float distance);
void destroyPlanet(Planet *planet);