/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the prototypes and interfaces 
*               required to interact with WarpSpace class objects.
*********************************************************************/
#ifndef WARPSPACE_HPP
#define WARPSPACE_HPP
#include "space.hpp"
#include "aGuy.hpp"
#include "menuNarration.hpp"
#include "menuValidate.hpp"

class WarpSpace : public Space
{
private:

    Space* boardPtr[24][10];
    items itemBoard[24][10];
    Guy* player;
    Space** spaceArrayPtr;

public:

    WarpSpace();
    void setRoomPtrs();
    void setItems(int, int);
    void setSpacePtrs(Space**);
    void setPlayerPtr(Guy*);
    void printRoom();
    void setItemBoard(int, int, items);
    items getItemBoard(int, int);
    void detect();
    ~WarpSpace();

};

#endif