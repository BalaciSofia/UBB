#include "Repo.h"

Repo* createRepo() {
	Repo *repository = malloc(sizeof(Repo));
	if (repository == NULL)
		return NULL;
	repository->elements = malloc(sizeof(TElem));
	repository->capacity = 1;
	repository->length = 0;
	return repository;
}

void resize(Repo *r) {

	/*r->capacity *= 2;
	TElem *aux = malloc(sizeof(TElem) * r->capacity);
	for (int i = 0; i < r->length; ++i)
		aux[i] = r->elements[i];
	free(r->elements);
	r->elements = aux;*/

	r->capacity *= 2;
	TElem *aux = realloc(r->elements, r->capacity * sizeof(TElem));
	r->elements = aux;
}

void destroyRepo(Repo *r)
{
	for (int i = 0; i < r->length; ++i)
		destroyPlanet(r->elements[i]);
	free(r->elements);
	free(r);
}

void addPlanet(Repo *repo, Planet *p) {
	if (repo->length == repo->capacity)
		resize(repo);
	repo->elements[repo->length++] = p;
}