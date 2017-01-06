#include "display.h"

void displayMenu(Game *game)
{
	int i,j;
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);
	for (i = 0; i < BOARD_HEIGHT+2; i++)
	{
		for (j = 0; j < BOARD_WIDTH+30; j++)
		{
			putCharXY(j, i, 32);
		}
	}
	putStringXY((BOARD_WIDTH + 26)/2-27, 2, "******************************************************");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 3, "*  *********	 **    *       *       *  *   ******    *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 4, "*  *          ***   *      * *      * *    *         *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 5, "*  *********	 * **  *     *****     **     ****      *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 6, "*          *	 *  ** *    *     *    * *    *         *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 7, "*  *********  *   ***   *       *   *  *   ******    *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 8, "******************************************************");

	putStringXY(MENU_X, MENU_START - 1, "MENU: ");
	putStringXY(MENU_X, MENU_START, "NEW GAME");
	putStringXY(MENU_X, MENU_START + 1, "SCORE LIST \\ NOT AVAILABLE YET");
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
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);
	for (i; i <= MENU_END; i++)
	{
		putCharXY(MENU_X - 2, i, SPACE);
	}
	color(DEFAULT_BACKGROUND_COLOR, MENU_POINTER_COLOR);
	putCharXY(game->menuSelectX, game->menuSelectY, MENU_ARROW);
}

void newGame(Game *game)
{
	int i = 0, j = 0;
	clearScreen();
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);
	for (i = 0; i < BOARD_HEIGHT + 2; i++)
	{
		for (j = 0; j < BOARD_WIDTH + 30; j++)
		{
			putCharXY(j, i, 32);
		}
	}
	color(BACKGROUND_COLOR, WALL_COLOR);
	for (i = 0; i <= BOARD_HEIGHT; i++)
	{
		putCharXY(0, i, SIDE_WALL);
		putCharXY(BOARD_WIDTH, i, SIDE_WALL);
	}
	color(DEFAULT_BACKGROUND_COLOR, WALL_COLOR);
	for (i=0; i <= BOARD_WIDTH; i++)
	{
		putCharXY(i, 0, DOWN_WALL);
		putCharXY(i, BOARD_HEIGHT, UPPER_WALL);
	}
	color(BACKGROUND_COLOR, BACKGROUND_COLOR);
	for (i = 1; i < BOARD_WIDTH; i++)
	{
		for (j = 1; j < BOARD_HEIGHT; j++)
		{
			putCharXY(i, j, BACKGROUND);
		}
	}
	color(DEFAULT_BACKGROUND_COLOR, WALL_COLOR);
	for (i = BOARD_WIDTH + 1; i < BOARD_WIDTH + 24; i++)
	{
		putCharXY(i, 0, DOWN_WALL);
	}
	for (j = BOARD_WIDTH + 1; j < BOARD_WIDTH + 24; j++)
	{
		putCharXY(j, 9, UPPER_WALL);
		putCharXY(j, BOARD_HEIGHT, UPPER_WALL);
	}
	for (i = 1; i < BOARD_HEIGHT; i++)
	{
		putCharXY(BOARD_WIDTH + 23, i, SIDE_WALL);
	}

	game->snakeX[0] = BOARD_WIDTH / 2;
	game->snakeY[0] = BOARD_HEIGHT / 2;
	color(BACKGROUND_COLOR, HEAD_COLOR);
	putCharXY(game->snakeX[0], game->snakeY[0], SNAKE_BODY);
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);
	putStringXY(BOARD_WIDTH + 2, 2, "YOUR SCORE:");
	putStringXY(BOARD_WIDTH + 2, 3, "Controls:");
	putStringXY(BOARD_WIDTH + 2, 4, "q - quit");
	putStringXY(BOARD_WIDTH + 2, 5, "r - restart");
	putStringXY(BOARD_WIDTH + 2, 6, "wsad - move");
	putStringXY(BOARD_WIDTH + 2, 13, "Eat apple.");
	putStringXY(BOARD_WIDTH + 2, 14, "Be bigger.");
	putStringXY(BOARD_WIDTH + 2, 15, "Don't hit wall.");
	putStringXY(BOARD_WIDTH + 2, 16, "Don't hit yourself.");
	putStringXY(BOARD_WIDTH + 2, 18, "Good luck!");
	putStringXY(BOARD_WIDTH + 2, 19, "Have fun!");
	game->snakeLength = 1;
	color(BACKGROUND_COLOR, APPLE_COLOR);
	drawApple(game);
}

void drawBoard(Game *game)
{
	int i = 0;
	color(BACKGROUND_COLOR, BACKGROUND_COLOR);
	putCharXY(game->snakeX[game->snakeLength], game->snakeY[game->snakeLength], BACKGROUND);
	color(BACKGROUND_COLOR, HEAD_COLOR);
	putCharXY(game->snakeX[0], game->snakeY[0], SNAKE_BODY);
	color(BACKGROUND_COLOR, BODY_COLOR);
	if (game->snakeLength > 1)putCharXY(game->snakeX[game->snakeLength-1], game->snakeY[game->snakeLength-1], SNAKE_BODY);

	
	for (i = 1; i < game->snakeLength; i++)
	{
		putCharXY(game->snakeX[i], game->snakeY[i], SNAKE_BODY);
	}
	color(BACKGROUND_COLOR, APPLE_COLOR);
}

void drawApple(Game *game)
{
	srand(time(NULL));
	int i = 0;
	int error = 0;
	
	do 
	{
		game->appleX = 1 + (int)(rand() / (RAND_MAX + 1.0) * (BOARD_WIDTH - 1));
		game->appleY = 1 + (int)(rand() / (RAND_MAX + 1.0) * (BOARD_HEIGHT - 1));
		for (i; i < game->snakeLength; i++)
		{
			if (game->appleX == game->snakeX[i])
			{
				error = 1;
				break;
			}
			else
				error = 0;
		}
	} while (error == 1);
		
	

	putCharXY(game->appleX, game->appleY, UNRIPE_APPLE);
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);
	putCharXY(BOARD_WIDTH + 15, 2, ' ');
	printf("%d", game->snakeLength-1);
	
}

void drawFinish(Game *game)
{
	color(BACKGROUND_COLOR, HEAD_COLOR);
	putStringXY((BOARD_WIDTH + 25) / 2 -5 , BOARD_HEIGHT / 2, "GAME OVER");
	putStringXY((BOARD_WIDTH + 25) / 2 -5 , BOARD_HEIGHT / 2 + 1, "SCORE :");
	printf(" %d POINTS", game->snakeLength - 1);
}