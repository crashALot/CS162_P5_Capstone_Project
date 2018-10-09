/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the prototypes and interfaces 
*               required to interact with CreateRooms class objects.
*********************************************************************/
#ifndef CREATEROOMS_HPP
#define CREATEROOMS_HPP
#include "itemSpace.hpp"
#include "startSpace.hpp"
#include "warpSpace.hpp"
#include "fightSpace.hpp"
#include "aGuy.hpp"
#include "space.hpp"

class CreateRooms
{
private:

    ItemSpace* topPtr, *bottomPtr;
    FightSpace* rightPtr, *leftPtr;
    WarpSpace* topRightPtr, *bottomLeftPtr;
    StartSpace* centerPtr;
    Guy* playerPtr;
    Space* spaceArray[5];

public:

    CreateRooms();
    //Guy* getPlayerPtr();
    ItemSpace* getTopPtr();
    ItemSpace* getBottomPtr();
    FightSpace* getRightPtr();
    FightSpace* getLeftPtr();
    WarpSpace* getTopRightPtr();
    WarpSpace* getBottomLeftPtr();
    StartSpace* getCenterPtr();
    void setPlayerPtr(Guy*);
    void createSpaceArray();
    Space** getSpaceArray();
    ~CreateRooms();

};

#endif