#include "display.h"

void displayMenu(Game *game)
{
	putStringXY(0, 0, "*******");
	putCharXY(0, 1, '*');
	putCharXY(6, 1, '*');
	putStringXY(0, 2, "*******");
	putStringXY(1, 1, "SNAKE");

	putStringXY(MENU_X, MENU_START-1, "MENU:");
	putStringXY(MENU_X, MENU_START, "NEW GAME");
	putStringXY(MENU_X, MENU_START+1, "SCORE");
	putStringXY(MENU_X, MENU_START+2, "EXIT");

	displayMenuSelectIcon(game);

}

void displayMenuSelectIcon(Game *game)
{
	int i = 0;
	if (game->menuSelectX != MENU_X-2)
	{
		game->menuSelectX = MENU_X-2;
		game->menuSelectY = MENU_START;
	}
	for (i = MENU_START; i <= MENU_END; i++)
	{
		putCharXY(MENU_X-2, i, 32);
	}
	putCharXY(game->menuSelectX, game->menuSelectY, MENUSELECT);
}

void newGame(Game *game)
{
	int i = 0, j = 0;
	clearScreen();
	for (i = 0; i <= BOARD_WIDTH; i++)
	{
		for (j = 0; j <= BOARD_HEIGHT; j++)
		{
			if (i < 2 || i > BOARD_WIDTH - 2 || j == 0 || j == BOARD_HEIGHT)
				putCharXY(i, j, WALL);
			else
				putCharXY(i, j, BACKGROUND);
		}
	}
	game->headX = BOARD_WIDTH / 2;
	game->headY = BOARD_HEIGHT / 2;

	putCharXY(game->headX, game->headY, SNAKE);
	putStringXY(BOARD_WIDTH + 2, 2, "Control your SNAKE with ARROW keys");
	putStringXY(BOARD_WIDTH + 2, 3, "q - quit");
	putStringXY(BOARD_WIDTH + 2, 4, "r - restart");
}

void drawBoard(Game *game)
{
	int i = 0, j = 0;
	for (i = 2; i <= BOARD_WIDTH - 2; i++)
	{
		for (j = 1; j <= BOARD_HEIGHT - 1; j++)
		{
			putCharXY(i, j, BACKGROUND);
		}
	}
	putCharXY(game->headX, game->headY, SNAKE);

}