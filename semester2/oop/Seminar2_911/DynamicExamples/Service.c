#include "Service.h"
Service *createService(Repo *r)
{
	Service *service = malloc(sizeof(Service));
	service->repo = r;
	return service;
}

//Planet *getPlanets(Service *s);