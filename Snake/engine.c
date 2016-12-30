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
				putStringXY(MENU_X, MENU_END + 1, "Wybrales NOWA GRE! NACIŒNIJ COKOLWIEK ABY KONTYNUWAC!");
				getKey();
				engine(game);
				break;
			case (MENU_START + 1):
				putStringXY(MENU_X, MENU_END + 1, "Wybrales liste wynikow! NACIŒNIJ COKOLWIEK ABY KONTYNUWAC!");
				break;
			case (MENU_START + 2):
				putStringXY(MENU_X, MENU_END + 1, "Wybrales KONIEC! Dziekuje za gre. NACIŒNIJ COKOLWIEK ABY KONTYNUWAC!");
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
		do
		{
			key = getKey();
			if (move(key, game) == 1)
			{
				drawBoard(game);
			}
		} while (move(key,game) == 1);
	}
}

int move(char key, Game *game)
{
	if (key == LEFT_ARROW)
	{
		if (game->headX > 2)
		{
			game->headX--;
			return 1;
		}
	}
	else if (key == RIGHT_ARROW)
	{
		if (game->headX < BOARD_WIDTH-2)
		{
			game->headX++;
			return 1;
		}
	}
	else if (key == UP_ARROW)
	{
		if (game->headY > 1)
		{
			game->headY--;
			return 1;
		}
	}
	else if (key == DOWN_ARROW)
	{
		if (game->headY < BOARD_HEIGHT-1)
		{
			game->headY++;
			return 1;
		}
	}
	else if (key == 'q')
	{
		// END
	}
	else if (key == 'r')
	{
		// RESTART
	}
}