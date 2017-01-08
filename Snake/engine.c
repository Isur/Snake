#include "engine.h"

void menuControl(Game *game) // sterowanie menu
{
	char key;
	int speed = 0;
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
			case (MENU_START):	// wybor ustawien gry
				putStringXY(MENU_X, MENU_END + 1, "CHOOSE SPEED LEVEL[1-4]: ");
				do
				{
					game->speed = getKey() - 48;
				} while (game->speed < 1 || game->speed > 4);
				printf("%d", game->speed);
				switch (game->speed)
				{	// od razu zmienia game->speed na wartosc uzywana w funkcji Sleep()
				case 1: game->speed = 100; break;
				case 2: game->speed = 75; break;
				case 3: game->speed = 50; break;
				case 4: game->speed = 25; break;
				default: break;
				}
				putStringXY(MENU_X, MENU_END + 2, "CHOOSE OBSTACLE LEVEL[1-4]: ");
				do
				{
					game->obstacle = getKey() - 48;
				} while (game->obstacle < 1 || game->obstacle > 4);
				printf("%d", game->obstacle);
				switch (game->obstacle)
				{ // od razu oblicza ilosc przeszkod
				case 1: game->obstacle = 0; break;
				case 2: game->obstacle = (int)BOARD_WIDTH*BOARD_HEIGHT / 256; break;
				case 3: game->obstacle = (int)BOARD_WIDTH*BOARD_HEIGHT / 128; break;
				case 4: game->obstacle = (int)BOARD_WIDTH*BOARD_HEIGHT / 64; break;
				default: break;
				}
				putStringXY(MENU_X, MENU_END + 3, "NICK[max 10 chars]: ");
				fgets(game->nick, 11, stdin);
				game->nick[strlen(game->nick) - 1] = '\0';
				wait(1000); 
				engine(game);
				break;
			case (MENU_START + 1):
				displayScore(game);
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
	srand(time(NULL));
	char key;
	char direction = 's';
	int i = 0;
	newGame(game);
	while (1) 
	{
		if (kbhit())	// czeka na przycisk
		{
			key = getKey();
			switch (key)
			{	// nie mozna wybrac przeciwnego kierunku, chyba ze snake jest dlugosci 1
			case 'w': if (direction != 'd' || game->snakeLength == 1)direction = 'u'; break;
			case 's': if (direction != 'u' || game->snakeLength == 1)direction = 'd'; break;
			case 'a': if (direction != 'r' || game->snakeLength == 1)direction = 'l'; break;
			case 'd': if (direction != 'l' || game->snakeLength == 1)direction = 'r'; break;
			case 'r': direction = 's'; newGame(game); break;
			case 'q': finish(game); break;
			default: break;
			}
		}
		if (game->snakeX[0] == game->appleX && game->snakeY[0] == game->appleY) // zbieranie jablek
		{
			if (game->apple == 0) finish(game);	// niedojrzale jablko
			else 
			{
				game->snakeLength++;
				drawApple(game);
			}
		}

		// 3s pauzy po przegranej
		for (i = 1; i < game->snakeLength; i++)
		{
			if (game->snakeX[0] == game->snakeX[i] && game->snakeY[0] == game->snakeY[i])
			{
				wait(3 * 1000);
				finish(game);
			}
		}
		for (i = game->snakeLength; i > 0; i--) // zapisanie pozycji odpowiednich
		{
			game->snakeX[i] = game->snakeX[i - 1];
			game->snakeY[i] = game->snakeY[i - 1];
		}
		if (game->apple == 0) // dojrzewanie jabkla 
		{
			i = random(0, 50);
			if (i == 3) ripeningApple(game);
			
		}
		move(game, direction);
	}

}

void move(Game *game, char direction)
{
	int i = 0;
	switch (direction)
	{ // wykonywanie ruchu, przegrana na scianach
	case 'u': if (game->snakeY[0] == 1) { wait(3 * 1000); finish(game); } if (game->snakeY[0] > 1) game->snakeY[0]--; break;
	case 'd': if (game->snakeY[0] == BOARD_HEIGHT - 1) { wait(3 * 1000); finish(game); } if (game->snakeY[0] < BOARD_HEIGHT - 1) game->snakeY[0]++; break;
	case 'l': if (game->snakeX[0] == 1) { wait(3 * 1000); finish(game); }; if (game->snakeX[0] > 1) game->snakeX[0]--; break;
	case 'r': if (game->snakeX[0] == BOARD_WIDTH - 1) { wait(3 * 1000); finish(game); } if (game->snakeX[0] < BOARD_WIDTH - 1) game->snakeX[0]++; break;
	case 's': break;
	default: break;
	}
	for (i = 0; i < game->obstacle; i++) // sprawdzanie czy nie ma przeszkody
	{
		if (game->snakeX[0] == game->obstacleX[i] && game->snakeY[0] == game->obstacleY[i])
		{
			wait(3 * 1000);
			finish(game);
			break;
		}
	}

	drawBoard(game); // rysowanie

	wait(game->speed); // szybkosc zalezy od gracza
}

void finish(game)
{
	clearScreen();
	drawFinish(game); //rysowanie planszy konczacej
	saveScore(game);  // zapis wyniku do pliku
	displayMenu(game); // powrot do menu
	menuControl(game);
}

int random(int min, int max)
{
	int tmp;
	if (max >= min)
		max -= min;
	else
	{
		tmp = min - max;
		min = max;
		max = tmp;
	}
	return max ? (rand() % max + min) : min;
}

void saveScore(Game *game)
{
	FILE *score_file;
	score_file = fopen("score.sc", "ab");
	fprintf(score_file, "%d - %s\n", game->snakeLength-1, game->nick); // kazda linia to: ilosc punktow - nick
	fclose(score_file);
}