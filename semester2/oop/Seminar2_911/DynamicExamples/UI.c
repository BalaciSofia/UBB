#include "UI.h"

UI* createUI(Service *s)
{
	UI *ui = malloc(sizeof(UI));
	ui->service = s;
	return ui;
}

void printMenu()
{
	printf("0 - Exit\n");
	printf("1 - Print All\n");
	printf("\nEnter command: ");
}

void printAll(Service *service)
{
	for (int i = 0; i < service->repo->length; ++i)
	{
		printf("%s %s %f\n", 
			((Planet*)service->repo->elements[i])->name, 
			((Planet*)service->repo->elements[i])->type, 
			((Planet*)service->repo->elements[i])->distance
		);
	}
}

void start(UI *ui)
{
	while (1)
	{
		printMenu();
		int command;
		scanf("%d", &command);
		switch (command)
		{
		case 0:
			return;
		case 1:
			printAll(ui->service);
			break;
		case 2:
			//add
			break;
		}
	}
}