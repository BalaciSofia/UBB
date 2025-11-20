#define _CRT_SECURE_NO_WARNINGS
#include "Planet.h"

Planet* createPlanet(char *name, char *type, float distance) {
	Planet *planet = malloc(sizeof(Planet));
	if (planet == NULL)
		return NULL;
	planet->name = malloc(sizeof(char) * (strlen(name) + 1));
	planet->type = malloc(sizeof(char) * (strlen(type) + 1));
	strcpy(planet->name, name);
	strcpy(planet->type, type);
	planet->distance = distance;
	return planet;
}

void destroyPlanet(Planet *planet) {
	if (planet == NULL)
	{
		printf("Planet already destroyed!\n");
		return;
	}
	free(planet->name);
	free(planet->type);
	free(planet);
}