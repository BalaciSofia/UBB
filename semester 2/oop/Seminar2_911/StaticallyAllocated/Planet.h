#pragma once

typedef struct {
	char name[20];
	char type[20];
	float distance;
}Planet;

Planet createPlanet(char *name, char *type, float distance);
char *toStringPlanet(Planet p);