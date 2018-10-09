/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the prototypes and interfaces 
*               required to interact with ItemSpace class objects.
*********************************************************************/
#ifndef ITEMSPACE_HPP
#define ITEMSPACE_HPP
#include "space.hpp"
#include "aGuy.hpp"
#include "menuNarration.hpp"
#include "menuValidate.hpp"

class ItemSpace : public Space
{
private:

    Space* boardPtr[20][20];
    items itemBoard[20][20];
    char itemList[6];
    Guy* player;

public:

    ItemSpace();
    void setRoomPtrs();
    void setItems(int, int);
    void setPlayerPtr(Guy*);
    void printRoom();
    void setItemBoard(int, int, items);
    items getItemBoard(int, int);
    void detect();
    ~ItemSpace();

};

#endif