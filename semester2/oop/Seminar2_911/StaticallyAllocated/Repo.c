#include "Repo.h"

Repo createRepo() {
	Repo repository;
	repository.length = 0;
	return repository;
}

void addPlanet(Repo *repo, Planet p) {
	repo->planets[repo->length++] = p;
}