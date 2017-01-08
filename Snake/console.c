#include "console.h"
#include "config.h"

void prepareScreen()
{
	HANDLE wHnd;   // uchwyt
	HANDLE rHnd;    
    CONSOLE_CURSOR_INFO cci;		// ustawienie kursora
    cci.dwSize = 1;
    cci.bVisible = 0;
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleCursorInfo(wHnd, &cci);
    system("chcp 852");	// kodowanie cp852 dla planszy
    system("CLS");		
	SetConsoleTitle(TEXT("SNAKE"));	// tytul
	SMALL_RECT windowSize = { 0, 0, BOARD_WIDTH+25, BOARD_HEIGHT };	// ustawienia okna
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	COORD bufferSize = { BOARD_WIDTH+26, BOARD_HEIGHT+1 };
	SetConsoleScreenBufferSize(wHnd, bufferSize);
}

void clearScreen()
{
    system("CLS");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 2, "******************************************************");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 3, "*  *********	 **    *       *       *  *   ******    *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 4, "*  *          ***   *      * *      * *    *         *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 5, "*  *********	 * **  *     *****     **     ****      *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 6, "*          *	 *  ** *    *     *    * *    *         *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 7, "*  *********  *   ***   *       *   *  *   ******    *");
	putStringXY((BOARD_WIDTH + 26) / 2 - 27, 8, "******************************************************");
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

void color(int bgColor, int fgColor)
{
	HANDLE hand;
	hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, bgColor * 16 | fgColor); // ustawienie kolorów,  background | foreground
}

void wait(int f)
{
	Sleep(f);
}