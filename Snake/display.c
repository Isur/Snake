#include "display.h"

void displayMenu(Game *game)
{
	putStringXY(2, 2, "******************************************************");
	putStringXY(2, 3, "*  *********	 **    *       *       *  *   ******    *");
	putStringXY(2, 4, "*  *          ***   *      * *      * *    *         *");
	putStringXY(2, 5, "*  *********	 * **  *     *****     **     ****      *");
	putStringXY(2, 6, "*          *	 *  ** *    *     *    * *    *         *");
	putStringXY(2, 7, "*  *********  *   ***   *       *   *  *   ******    *");
	putStringXY(2, 8, "******************************************************");

	putStringXY(MENU_X, MENU_START - 1, "MENU: ");
	putStringXY(MENU_X, MENU_START, "NEW GAME");
	putStringXY(MENU_X, MENU_START + 1, "SCORE LIST \\ NOT AVIABLE IN BETA");
	putStringXY(MENU_X, MENU_START + 2, "EXIT");

	displayMenuSelectIcon(game);
}

void displayMenuSelectIcon(Game *game)
{
	int i = MENU_START;
	if (game->menuSelectX != MENU_X - 2)
	{
		game->menuSelectX = MENU_X - 2;
		game->menuSelectY = MENU_START;
	}
	for (i; i <= MENU_END; i++)
	{
		putCharXY(MENU_X - 2, i, SPACE);
	}
	putCharXY(game->menuSelectX, game->menuSelectY, MENU_ARROW);
}

void newGame(Game *game)
{
	int i = 0, j = 0;
	clearScreen();
	for (i = 0; i <= BOARD_HEIGHT; i++)
	{
		putCharXY(0, i, SIDE_WALL);
		putCharXY(BOARD_WIDTH, i, SIDE_WALL);
	}
	for (i=0; i <= BOARD_WIDTH; i++)
	{
		putCharXY(i, 0, DOWN_WALL);
		putCharXY(i, BOARD_HEIGHT, UPPER_WALL);
	}
	for (i = 1; i < BOARD_WIDTH; i++)
	{
		for (j = 1; j < BOARD_HEIGHT; j++)
		{
			putCharXY(i, j, BACKGROUND);
		}
	}
	game->snakeX[0] = BOARD_WIDTH / 2;
	game->snakeY[0] = BOARD_HEIGHT / 2;
	putCharXY(game->snakeX[0], game->snakeY[0], SNAKE_BODY);
	putStringXY(BOARD_WIDTH + 2, 2, "YOUR SCORE:");
	putStringXY(BOARD_WIDTH + 2, 4, "q - quit");
	putStringXY(BOARD_WIDTH + 2, 5, "r - restart");
	game->snakeLength = 1;
	drawApple(game);
}

void drawBoard(Game *game)
{
	int i = 0, j = 0;
	for (i = 1; i < BOARD_WIDTH; i++)
	{
		for (j = 1; j < BOARD_HEIGHT; j++)
		{
			putCharXY(i, j, BACKGROUND);
		}
	}
	for (i = 0; i < game->snakeLength; i++)
	{
		putCharXY(game->snakeX[i], game->snakeY[i], SNAKE_BODY);
	}
	
	putCharXY(game->appleX, game->appleY, APPLE);
}

void drawApple(Game *game)
{
	game->appleX = 1 + (int)(rand() / (RAND_MAX + 1.0) * (BOARD_WIDTH - 1));
	game->appleY = 1 + (int)(rand() / (RAND_MAX + 1.0) * (BOARD_HEIGHT - 1));
	putCharXY(game->appleX, game->appleY, APPLE);
	putCharXY(BOARD_WIDTH + 15, 2, ' ');
	printf("%d", game->snakeLength);
	
}