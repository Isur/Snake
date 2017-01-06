#pragma once

#include "console.h"
#include "config.h"
#include <time.h>

typedef struct
{
    int menuSelectX;
    int menuSelectY;
    int appleX;
    int appleY;
    int snakeX[BOARD_HEIGHT*BOARD_WIDTH];
    int snakeY[BOARD_HEIGHT*BOARD_WIDTH];
	int prevSnakeX[BOARD_HEIGHT*BOARD_WIDTH];
	int prevSnakeY[BOARD_HEIGHT*BOARD_WIDTH];
    // int snakeBody[BOARD_HEIGHT*BOARD_WIDTH][]
    int nick;
	int snakeLength;
}Game;

void displayMenu(Game *game);
void displayMenuSelectIcon(Game *game);
void newGame(Game *game);
void drawBoard(Game *game);
void drawApple(Game *game);
void theEnd(Game *game);
void drawFinish(Game *game);