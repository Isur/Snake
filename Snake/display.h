#pragma once

#include "console.h"
#include "config.h"

typedef struct
{
	int menuSelectX;
	int menuSelectY;
	int headX;
	int headY;
	int bodyX[BOARD_WIDTH*BOARD_HEIGHT][BOARD_WIDTH];
	int bodyY[BOARD_WIDTH*BOARD_HEIGHT][BOARD_HEIGHT];
	int appleX;
	int appleY;
}Game;

void displayMenu();
void displayMenuSelectIcon();
void newGame(Game *game);
void drawBoard(Game *game);