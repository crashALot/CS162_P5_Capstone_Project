/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the prototypes and interfaces 
*               required to interact with SpaceMenu class objects.
*********************************************************************/
#ifndef SPACEMENU_HPP
#define SPACEMENU_HPP
#include "menuValidate.hpp"
#include "aGuy.hpp"
#include "createRooms.hpp"
#include "space.hpp"

class SpaceMenu
{
private:

    Guy* player;
    CreateRooms* roomPtr;
    Space* spacePtr;
    
public:

    SpaceMenu(CreateRooms*);
    int mainMenu();
    void playGame();
    int exitMenu();
    void printRoom();
    Guy* getPlayerPtr();
    CreateRooms* getRoomPtr();
    ~SpaceMenu();
    
};

#endif