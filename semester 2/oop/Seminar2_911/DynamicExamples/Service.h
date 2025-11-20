#pragma once
#include "Repo.h";
typedef struct {
	Repo *repo;
}Service;

Service* createService(Repo *r);