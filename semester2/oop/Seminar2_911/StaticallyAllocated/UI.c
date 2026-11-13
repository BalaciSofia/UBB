#include "UI.h"

UI createUI(Service *s)
{
	UI ui;
	ui.service = *s;
	return ui;
}

void printMenu()
{
	printf("0 - Exit\n");
	printf("\nEnter command: ");
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
			//add
			break;
		case 2:
			//print all
			break;
		}
	}
}