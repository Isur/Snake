/*
******************************************************
*  *********	**    *	      *	      *  *   ******  *
*  *			***   *  	 * *      * *    *       *
*  *********	* **  *	    *****     **     ******  *
*    	   *	*  ** *	   *     *    * *    *       *
*  *********    *   ***   *       *   *  *   ******  *
******************************************************
****************************
*                          *
* MADE BY Artur Bednarczyk *
* 2017 - Programowanie I   * 
*                          *
****************************
*/

#include "config.h"
#include "engine.h"
#include "console.h"
#include "display.h"

main()
{
    Game game;
    
    prepareScreen();
    displayMenu(&game);
	menuControl(&game);



    return 0;
}