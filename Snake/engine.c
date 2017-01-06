#include "engine.h"

void menuControl(Game *game)
{
	char key;
	while (1)
	{
		key = getKey();
		if (key == UP_ARROW)
		{
			if (game->menuSelectY > MENU_START)
			{
				game->menuSelectY--;
			}
		}
		else if (key == DOWN_ARROW)
		{
			if (game->menuSelectY < MENU_END)
			{
				game->menuSelectY++;
			}
		}
		displayMenuSelectIcon(game);
		if (key == ENTER)
		{
			game->menuSelectX = -1;
			switch (game->menuSelectY)
			{
			case (MENU_START):
				putStringXY(MENU_X, MENU_END + 1, "NEW GAME! CLICK SOMETHING TO CONTINUE");
				getKey();
				engine(game);
				break;
			case (MENU_START + 1):
				//putStringXY(MENU_X, MENU_END + 1, "SCORE LIST! CLICK SOMETHING TO CONTINUE");
				//getKey();
				menuControl(game);
				break;
			case (MENU_START + 2):
				putStringXY(MENU_X, MENU_END + 1, "EXIT! THANKS FOR PLAYING!");
				getKey();
				exit(1);
				break;
			}
			break;
		}
	}
}

void engine(Game *game)
{
	char key;
	char direction = 's';
	int i = 0;
	newGame(game);
	while (1) 
	{
		if (kbhit())
		{
			key = getKey();
			switch (key)
			{
			case 'w': if (direction == 'd' && game->snakeLength > 1) finish(game); direction = 'u'; break;
			case 's': if (direction == 'u' && game->snakeLength > 1) finish(game); direction = 'd'; break;
			case 'a': if (direction == 'r' && game->snakeLength > 1) finish(game); direction = 'l'; break;
			case 'd': if (direction == 'l' && game->snakeLength > 1) finish(game); direction = 'r'; break;
			case 'r': direction = 's'; newGame(game); break;
			case 'q': finish(game); break;
			default: break;
			}
		}
		if (game->snakeX[0] == game->appleX && game->snakeY[0] == game->appleY)
		{
			game->snakeLength++;
			drawApple(game);
		}

		for (i = 1; i < game->snakeLength; i++)
		{
			if (game->snakeX[0] == game->snakeX[i] && game->snakeY[0] == game->snakeY[i])
			{
				finish(game);
			}
		}
		for (i = game->snakeLength - 1; i > 0; i--)
		{
			game->snakeX[i] = game->snakeX[i - 1];
			game->snakeY[i] = game->snakeY[i - 1];
		}
		move(game, direction);
	}

}

void move(Game *game, char direction)
{
	switch (direction)
	{
	case 'u': if (game->snakeY[0] == 1) finish(game); if (game->snakeY[0] > 1) game->snakeY[0]--; break;
	case 'd': if (game->snakeY[0] == BOARD_HEIGHT - 1) finish(game); if (game->snakeY[0] < BOARD_HEIGHT - 1) game->snakeY[0]++; break;
	case 'l': if (game->snakeX[0] == 1) finish(game); if (game->snakeX[0] > 1) game->snakeX[0]--; break;
	case 'r': if (game->snakeX[0] == BOARD_WIDTH - 1) finish(game); if (game->snakeX[0] < BOARD_WIDTH - 1) game->snakeX[0]++; break;
	case 's': break;
	default: break;
	}
	drawBoard(game);
	Sleep(SPEED);
}

void finish(game)
{
	clearScreen();
	drawFinish(game);
	getKey();
	displayMenu(game);
	menuControl(game);
}