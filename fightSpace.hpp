/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the prototypes and interfaces 
*               required to interact with FightSpace class objects.
*********************************************************************/
#ifndef FIGHTSPACE_HPP
#define FIGHTSPACE_HPP
#include "space.hpp"
#include "aGuy.hpp"
#include "menuNarration.hpp"
#include "menuValidate.hpp"

class FightSpace : public Space
{
private:

    Space* boardPtr[10][10];
    items itemBoard[10][10];
    int monsterLocation[2];
    Guy* player;

public:

    FightSpace();
    void setRoomPtrs();
    void setItems(int, int);
    void setPlayerPtr(Guy*);
    void printRoom();
    void setItemBoard(int, int, items);
    items getItemBoard(int, int);
    void detect();
    void monsterMove();
    int getMonsterRow();
    int getMonsterCol();
    void fight();
    ~FightSpace();

};

#endif