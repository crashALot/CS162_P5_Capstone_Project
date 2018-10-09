/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the prototypes and interfaces 
*               required to interact with StartSpace class objects.
*********************************************************************/
#ifndef STARTSPACE_HPP
#define STARTSPACE_HPP
#include "space.hpp"
#include "aGuy.hpp"
#include "menuNarration.hpp"
#include "menuValidate.hpp"

class StartSpace : public Space
{
private:

    Space* boardPtr[16][16], *rightPtr, *leftPtr;
    items itemBoard[16][16];
    Guy* player;
    bool unlockedNS;

public:

    StartSpace();
    void setRoomPtrs();
    void setPlayerPtr(Guy*);
    void printRoom();
    void setItemBoard(int, int, items);
    items getItemBoard(int, int);
    void detect();
    void setRightPtr(Space*);
    void setLeftPtr(Space*);
    Space* getRightPtr();
    Space* getLeftPtr();
    Guy* getPlayerPtr();
    ~StartSpace();

};

#endif