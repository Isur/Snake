#pragma once
// only windows console functions:

void prepareScreen();
void putCharXY(int x, int y, char character);
void putStringXY(int x, int y, char *string);
char getKey();
void clearScreen();