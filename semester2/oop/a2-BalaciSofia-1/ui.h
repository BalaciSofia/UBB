#pragma once
#include "service.h"

typedef struct{
    Service *service;
}Ui;

Ui createUi(Service *s);
void start(Ui *ui);
void destroyUi(Ui *ui);