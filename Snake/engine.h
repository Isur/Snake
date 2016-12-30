#pragma once
#include "display.h"
#include "config.h"
#include "console.h"
// game engine
// movement
// scores
// finish game

void menuControl(Game *game);
void engine(Game *game);
int move(char key, Game *game);
int finish(Game *game);
