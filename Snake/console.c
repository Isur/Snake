#include "console.h"
#include "config.h"

void prepareScreen()
{
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
    system("chcp 852");
    system("CLS");

	HANDLE wHnd;    // Handle to write to the console.
	HANDLE rHnd;    // Handle to read from the console.
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle("SNAKE");
	SMALL_RECT windowSize = { 0, 0, 100, BOARD_HEIGHT + 2 };
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
	COORD bufferSize = { 10, 10 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
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
    while(*string)
    {
        putCharXY(x++, y, *string++);
    }
}

char getKey()
{
    return getch();
}