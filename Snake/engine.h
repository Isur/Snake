#pragma once

#include "display.h"
#include "config.h"
#include "console.h"


void menuControl(Game *game);
void engine(Game *game);
void move(Game *game, char direction);
void finish(Game *game);