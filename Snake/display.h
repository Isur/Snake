#pragma once

#include "console.h"
#include "config.h"
#include <time.h>
#include <stdlib.h>

typedef struct
{
    int menuSelectX;	// kursor menu
    int menuSelectY;
    int appleX;			// pozycja jablka
    int appleY;
    int snakeX[BOARD_HEIGHT*BOARD_WIDTH];	// pozycje snake'a
    int snakeY[BOARD_HEIGHT*BOARD_WIDTH];
    int snakeLength;	// dlugosc snake'a
	int snakePrevX;		//ostatnia pozycja
	int snakePrevY;	
	int speed;			// szybkosc
	int obstacle;		// ilosc przeszkod
	int obstacleX[(BOARD_HEIGHT*BOARD_WIDTH) / 4];	// pozycje przeszkod
	int obstacleY[(BOARD_HEIGHT*BOARD_WIDTH) / 4];
	char nick[11];	// nick
	int apple;		// czy dojrzale czy nie
}Game;

void displayMenu(Game *game);
void displayMenuSelectIcon(Game *game);
void newGame(Game *game);
void drawBoard(Game *game);
void drawApple(Game *game);
void drawFinish(Game *game);
void animationMenu(Game *game);
void displayScore(Game *game);
void ripening(Game *game);