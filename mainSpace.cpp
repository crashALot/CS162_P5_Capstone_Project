/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This program runs a small map based game based on 
*               finding items and accessing rooms within a given
*               time limit. Can you find the exit in time?
*********************************************************************/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "createRooms.hpp"
#include "spaceMenu.hpp"

int main()
{
    srand(time(NULL)); // Seed used for random number generators
    int go=1; // Sentinel value to break while loop
    while(go)
    {
    CreateRooms newMap;
    SpaceMenu newGame(&newMap);
    go=newGame.mainMenu();
    if (go!=0)
        go=newGame.exitMenu();
    }
    std::cout << "   ************ Thank you for playing! See you again soon! ************" << std::endl << std::endl;
	return 0;
}
