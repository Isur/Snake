#include "engine.h"
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW	77
#define ENTER 13

void menuControl(Game *game)
{
	char key;
	while (1)
	{
		key = getKey();
		if (key == UP_ARROW && game->menuSelectY > 5)
		{
			game->menuSelectY--;
			displayMenuSelectIcon(game);
		}
		else if (key == DOWN_ARROW && game->menuSelectY < 7)
		{
			game->menuSelectY++;
			displayMenuSelectIcon(game);
		}
		else if(key == ENTER)
		{
			switch (game->menuSelectY)
			{
			case (MENU_START):
				putStringXY(MENU_X, MENU_END + 1, "Wybrales NOWA GRE! NACI�NIJ COKOLWIEK ABY KONTYNUWAC!");
				getKey();
				engine(game);
				break;
			case (MENU_START + 1):
				putStringXY(MENU_X, MENU_END + 1, "Wybrales liste wynikow! NACI�NIJ COKOLWIEK ABY KONTYNUWAC!");
				break;
			case (MENU_START + 2):
				putStringXY(MENU_X, MENU_END + 1, "Wybrales KONIEC! Dziekuje za gre. NACI�NIJ COKOLWIEK ABY KONTYNUWAC!");
				break;
			}
			break;
		}
	}
}
void engine(Game *game)
{
	char key;
	int changeDirection = 0;
	newGame(game);
	while (1)
	{
		
	}
}

int move(char key, Game *game)
{
	if (key == 'q')
	{
		finish(game);
	}
	else if (key == 'r')
	{
		newGame(game);
	}
}

int finish(Game *game)
{
	clearScreen();
	putStringXY(1, 2, "KONIEC GRY!");
}