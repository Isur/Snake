/********************************************
*                                           *
*     Copyright 2016 by Artur Bednarczyk    *
*     Version: 0.0                          *
*                                           *
*********************************************/
#include "config.h"
#include "engine.h"
#include "console.h"
#include "display.h"

main()
{
	Game game;

	prepareScreen(&game);
	displayMenu(&game);
	menuControl(&game);

	getKey();
	return 0;
}