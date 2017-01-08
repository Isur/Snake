#pragma once

#include "console.h"
#include "config.h"
#include <time.h>
#include <stdlib.h>

typedef struct
{
    int menuSelectX;
    int menuSelectY;
    int appleX;
    int appleY;
    int snakeX[BOARD_HEIGHT*BOARD_WIDTH];
    int snakeY[BOARD_HEIGHT*BOARD_WIDTH];
    int snakeLength;
	int snakePrevX;
	int snakePrevY;
	int speed;
	int obstacle;
	int obstacleX[(BOARD_HEIGHT*BOARD_WIDTH) / 4];
	int obstacleY[(BOARD_HEIGHT*BOARD_WIDTH) / 4];
	char nick[11];
	int apple;
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