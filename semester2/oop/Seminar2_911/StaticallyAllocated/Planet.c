#define _CRT_SECURE_NO_WARNINGS
#include "Planet.h"
#include <string.h>

Planet createPlanet(char *name, char *type, float distance) {
	Planet planet;
	strcpy(planet.name, name);
	strcpy(planet.type, type);
	planet.distance = distance;
	return planet;
}