#include "Service.h"
Service createService(Repo *r)
{
	Service service;
	service.repo = *r;
	return service;
}