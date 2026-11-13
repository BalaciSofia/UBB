#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>
#include "UI.h"

void pointers()
{
    printf("Hello World!\n");
    int x;
    scanf("%d", &x);
    printf("x - value: %d, address: %d\n", x, &x);
    int *y = (int *)malloc(sizeof(int));
    *y = 10;
    printf("y - value: %d, address: %d", *y, y);

    free(y);

    _CrtDumpMemoryLeaks();
}

void populateRepo(Repo *r)
{
    Planet *p1 = createPlanet("p1", "t1", 100);
    Planet *p2 = createPlanet("p2", "t2", 200);
    addPlanet(r, p1);
    addPlanet(r, p2);
}

int main()
{
    Repo *repository = createRepo();
    Service *s = createService(repository);
    UI *ui = createUI(s);
    populateRepo(repository);
    start(ui);
    destroyRepo(repository);

    _CrtDumpMemoryLeaks();

    return 0;
}