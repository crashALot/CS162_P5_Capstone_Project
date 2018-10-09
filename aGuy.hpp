/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the prototypes and interfaces 
*               required to interact with Guy class objects.
*********************************************************************/
#ifndef AGUY_HPP
#define AGUY_HPP
#include <list>
#include "space.hpp"
#include "menuNarration.hpp"
#include "menuValidate.hpp"

enum axis {row, col};

class Guy
{
private:

    int steps, eastLimit, southLimit;
    int position[2];
    Space* whereAmINow;
    std::list<items> inventory;

public:

    Guy();
    void addInventory(items);
    void removeInventory(items);
    int checkInventorySize();
    void printInventory();
    bool checkForItem(items);
    void dropItem();
    void setSteps(int);
    void setPosition(int, int);
    void setLimits(int, int);
    void setWhereAmINow(Space*);
    void action(char);
    int getEastLimit();
    int getSouthLimit();
    int getSteps();
    int getPositionRow();
    int getPositionCol();
    Space* getWhereAmINow();
    ~Guy();

};

#endif