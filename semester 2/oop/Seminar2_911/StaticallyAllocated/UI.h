#pragma once
#include "Service.h"

typedef struct {
	Service service;
} UI;

UI createUI(Service *s);
