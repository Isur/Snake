#include "display.h"

void displayMenu(Game *game)
{
	int i,j;
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);	// tworzy plansze pod menu
	for (i = 0; i < BOARD_HEIGHT+2; i++)
	{
		for (j = 0; j < BOARD_WIDTH+30; j++)
		{
			putCharXY(j, i, 32);
		}
	}// menu:
	putStringXY((BOARD_WIDTH + 26)/2-27, 2,"******************************************************");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 3, "*  *********	 **    *       *       *  *   ******    *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 4, "*  *          ***   *      * *      * *    *         *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 5, "*  *********	 * **  *     *****     **     ****      *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 6, "*          *	 *  ** *    *     *    * *    *         *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 7, "*  *********  *   ***   *       *   *  *   ******    *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 8, "******************************************************");

	putStringXY(MENU_X, MENU_START - 1, "MENU: ");
	putStringXY(MENU_X, MENU_START, "NEW GAME");
	putStringXY(MENU_X, MENU_START + 1, "SCORE");
	putStringXY(MENU_X, MENU_START + 2, "EXIT");

	displayMenuSelectIcon(game);
}

void displayMenuSelectIcon(Game *game)
{
	int i = MENU_START;			// 'kursor menu'
	if (game->menuSelectX != MENU_X - 2)
	{
		game->menuSelectX = MENU_X - 2;
		game->menuSelectY = MENU_START;
	}
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);	// po przesunieciu w poprzednie miejsce wstawia spacje
	for (i; i <= MENU_END; i++)
	{
		putCharXY(MENU_X - 2, i, SPACE);
	}
	color(DEFAULT_BACKGROUND_COLOR, MENU_POINTER_COLOR);	// wstawianie nowego
	putCharXY(game->menuSelectX, game->menuSelectY, MENU_ARROW);
	color(DEFAULT_BACKGROUND_COLOR, BACKGROUND_COLOR);
}

void newGame(Game *game) // tworzenie nowej planszy
{
	int i = 0, j = 0;
	clearScreen(); // czyszczenie ca³ego ekranu
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);	// przygotowanie tla
	for (i = 0; i < BOARD_HEIGHT + 2; i++)
	{
		for (j = 0; j < BOARD_WIDTH + 30; j++)
		{
			putCharXY(j, i, 32);
		}
	}
	color(BACKGROUND_COLOR, WALL_COLOR);		// rysowanie scianek bocznych
	for (i = 0; i <= BOARD_HEIGHT; i++)
	{
		putCharXY(0, i, SIDE_WALL);
		putCharXY(BOARD_WIDTH, i, SIDE_WALL);
		putCharXY(BOARD_WIDTH + 23, i, SIDE_WALL);
	}
	color(DEFAULT_BACKGROUND_COLOR, WALL_COLOR);	// rysowanie scianek dolnych i gornych
	for (i=0; i < BOARD_WIDTH+24; i++)
	{
		putCharXY(i, 0, DOWN_WALL);
		putCharXY(i, BOARD_HEIGHT, UPPER_WALL);
		if (i > BOARD_WIDTH+1) putCharXY(i-1, 9, DOWN_WALL);
	}
	color(BACKGROUND_COLOR, BACKGROUND_COLOR);	 // rysowanie tla planszy dla snake'a
	for (i = 1; i < BOARD_WIDTH; i++)
	{
		for (j = 1; j < BOARD_HEIGHT; j++)
		{
			putCharXY(i, j, BACKGROUND);
		}
	}
	color(BACKGROUND_COLOR, WALL_COLOR);
	if (game->obstacle > 0)	// rysowanie przeszkod 
	{
		srand(time(NULL));
		for (i = 0; i < game->obstacle;i++)
		{
			do 
			{
				game->obstacleX[i] = random(1, BOARD_WIDTH - 1);										// pominiecie sprawdzania czy sie powtarzaja
				game->obstacleY[i] = random(1, BOARD_HEIGHT - 1);										// celowe, aby zapewnic odrobine losowosci
			} while (game->obstacleX[i] == BOARD_WIDTH / 2 && game->obstacleY[i] == BOARD_HEIGHT / 2);	// przy ilosci wyswietlonych przeszkod
			putCharXY(game->obstacleX[i], game->obstacleY[i], SIDE_WALL);
		}
	}
	
	game->snakeX[0] = BOARD_WIDTH / 2;	//ustalenie pozycji snake'a na srodku
	game->snakeY[0] = BOARD_HEIGHT / 2;
	color(BACKGROUND_COLOR, HEAD_COLOR);	// rysowanie snake'a
	putCharXY(game->snakeX[0], game->snakeY[0], SNAKE_BODY);
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR); // punkty i instrukcja
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
	drawApple(game);  // rysowanie jablka na planszy
}

void drawBoard(Game *game) // odswiezenie po kazdym ruchu
{
	int i = 0;
	color(BACKGROUND_COLOR, BACKGROUND_COLOR);
	putCharXY(game->snakeX[game->snakeLength], game->snakeY[game->snakeLength], BACKGROUND);	// na pozycji na ktorej juz snake'a nie ma rysuje sie tlo
	color(BACKGROUND_COLOR, HEAD_COLOR);
	putCharXY(game->snakeX[0], game->snakeY[0], SNAKE_BODY); // rysowanie glowy
	color(BACKGROUND_COLOR, BODY_COLOR);
	if (game->snakeLength > 1)putCharXY(game->snakeX[game->snakeLength-1], game->snakeY[game->snakeLength-1], SNAKE_BODY); // rysowanie konca

	
}

void drawApple(Game *game)
{
	srand(time(NULL));
	int i = 0;
	int error = 0;
	do	
	{
		game->appleX = random(1, BOARD_WIDTH - 1);
		game->appleY = random(1, BOARD_HEIGHT - 1);
		game->apple = random(0, 2);
		// sprawdza czy nie nie pojawia sie na snake'u 
		for (i = 0; i < game->snakeLength; i++)
		{
			if (game->appleX == game->snakeX[i] && game->appleY == game->snakeY[i])
			{
				error = 1;
				break;
			}
			else
				error = 0;
		}
		// sprawdza czy nie pojawi sie na przeszkodzie
		for (i = 0; i < game->obstacle; i++)
		{
			if (game->appleX == game->obstacleX[i] && game->appleY == game->obstacleY[i])
			{
				error = 1;
				break;
			}
			else
				error = 0;
		}
	} while (error == 1);
	
	if (game->apple == 0)
	{
		color(BACKGROUND_COLOR, UNRIPE_APPLE_COLOR);
	}else
		color(BACKGROUND_COLOR, APPLE_COLOR);
	putCharXY(game->appleX, game->appleY, UNRIPE_APPLE);
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);
	putCharXY(BOARD_WIDTH + 15, 2, ' ');
	printf("%d", game->snakeLength-1);
}

void ripeningApple(Game *game)
{
	game->apple = 1;
	color(BACKGROUND_COLOR, APPLE_COLOR);
	putCharXY(game->appleX, game->appleY, UNRIPE_APPLE);
}

void drawFinish(Game *game)
{	// ekran po zakonczeniu gry
	int i = 0;
	color(BACKGROUND_COLOR, 15);
	putStringXY((BOARD_WIDTH + 25) / 2 -4 , BOARD_HEIGHT / 2 -1, "GAME OVER");
	putCharXY((BOARD_WIDTH + 25) / 2 - 5, BOARD_HEIGHT / 2 + 1, SPACE);
	printf("%s", game->nick);
	putStringXY((BOARD_WIDTH + 25) / 2 -5 , BOARD_HEIGHT / 2 + 3, "YOUR SCORE:");
	putCharXY((BOARD_WIDTH + 25) / 2 - 4, BOARD_HEIGHT / 2 + 4, SPACE);
	printf("%d POINTS", game->snakeLength - 1);
	for (i = 2; i > 0; i--)
	{
		putCharXY((BOARD_WIDTH + 25) / 2 , BOARD_HEIGHT / 2 - 4, i+48);
		wait(1 * 1000);
	}
}

void displayScore(Game *game)
{
	int i = BOARD_WIDTH/2+7, j = 11, k = 1;
	char temp;
	char tempArray[2][6];
	color(DEFAULT_BACKGROUND_COLOR, DEFAULT_FOREGROUND_COLOR);
	clearScreen();
	FILE *scoreList;
	scoreList = fopen("score.sc", "rb");
	if(scoreList == NULL) putStringXY((BOARD_WIDTH + 25) / 2 - 5, BOARD_HEIGHT / 2 + 3, "FAILED TO OPEN FILE:");
	else
	{
		while (1)
		{
			temp = getc(scoreList);
			if (temp == EOF) break;
			putCharXY(BOARD_WIDTH-5, BOARD_HEIGHT - 3, SPACE);
			printf("Page: %d", k);
			if (temp == '\n') { j++; i = BOARD_WIDTH/2+6; }
			putCharXY(i, j, temp);
			i++;		
			if (j > 17)
			{
				putStringXY(26, BOARD_HEIGHT - 3, "CLICK - NEXT PAGE!");
				temp = getKey();
				if (temp == UP_ARROW || temp == DOWN_ARROW || temp == RIGHT_ARROW || temp == LEFT_ARROW) getKey();
				clearScreen();
				j = 11;
				i = BOARD_WIDTH / 2 + 7;
				k++;
			}
		
		}
		fclose(scoreList);
		putStringXY(26, BOARD_HEIGHT - 3, "LAST PAGE - CLICK - BACK TO MENU!");
		getKey();
		displayMenu(game);
		menuControl(game);
		
	}
}