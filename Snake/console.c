#include "console.h"
#include<Windows.h>
#include<stdio.h>
void prepareScreen()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	system("chcp 852");
	system("CLS");
}

void clearScreen()
{
	system("CLS");
}

void putCharXY(int x, int y, char character)
{
	COORD cursorPosition;
	cursorPosition.X = x;
	cursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
	printf("%c", character);
}

void putStringXY(int x, int y, char *string)
{
	while (*string)
	{
		putCharXY(x++, y, *string++);
	}
}

char getKey()
{
	return getch();	
}