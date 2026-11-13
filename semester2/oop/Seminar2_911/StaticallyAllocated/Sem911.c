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

int main()
{
    // Add repo, struct Planet {name, type, distance}
    // - add 2 planets to the repo
    Planet p1 = createPlanet("p1", "t1", 100);
    Planet p2 = createPlanet("p2", "t2", 200);
    Repo repository = createRepo();
    addPlanet(&repository, p1);
    addPlanet(&repository, p2);
    Service s = createService(&repository);
    UI ui = createUI(&s);
    start(&ui);
    return 0;
}