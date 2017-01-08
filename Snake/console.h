#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

// Windows:

void prepareScreen();
void putCharXY(int x, int y, char character);
void putStringXY(int x, int y, char *string);
char getKey();
void clearScreen();
void color(int bgColor, int fgColor);
void wait(int f);
