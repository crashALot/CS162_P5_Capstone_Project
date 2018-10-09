/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the methods and functions required 
*               to use Guy class objects. These objects represent
*               the player, and coordinate movement and inventory
*               status throughout the game.
*********************************************************************/
#include "aGuy.hpp"
#include <iostream>
#include <iomanip>
#include <list>

/********************************************************************* 
** Description: Guy::Guy()
*               Guy class default constructor
*********************************************************************/
Guy::Guy()
{
    steps=200;
    position[row]=-1;
    position[col]=-1;
    eastLimit=0;
    southLimit=0;
    whereAmINow=NULL;
}

/********************************************************************* 
** Description: void Guy::action(char actionIn)
*               Evaluates user input and directs player action in
*               response. Actions can include movement, inventory
*               operations, and game exit.
*********************************************************************/
void Guy::action(char actionIn)
{
    switch (actionIn)
    {
        case 'n':
        if ((position[row]-1)>=0)
            position[row]-=1;
        else
            std::cout << "You can not go any further North!" << std::endl;
        break;
        
        case 'e':
        if ((position[col]+1)<=eastLimit)
            position[col]+=1;
        else
            std::cout << "You can not go any further East!" << std::endl;
        break;
        
        case 's':
        if ((position[row]+1)<=southLimit)
            position[row]+=1;
        else
            std::cout << "You can not go any further South!" << std::endl;
        break;
        
        case 'w':
        if ((position[col]-1)>=0)
            position[col]-=1;
        else
            std::cout << "You can not go any further West!" << std::endl;
        break;
        
        case 'p':
            this->printInventory();
        break;
        
        case 'd':
            this->dropItem();
        break;
        
        case 'x':
            this->setSteps(-123);
        break;
        
        case 'i':
            instructions();
        break;
    }
    if (actionIn!='p' && actionIn!='d' && actionIn!='x' &&actionIn!='i')
        steps--;
}

/********************************************************************* 
** Description: void Guy::addInventory(items itemIn)
*               Adds a user specified item into the player inventory
*********************************************************************/
void Guy::addInventory(items itemIn)
{
    if (checkInventorySize()==3)
    {
        std::cout  << "   You cannot add any more items to your inventory!" << std::endl << std::endl;
    }
    else
    {
        if (checkForItem(key2)==true && itemIn==key2)
            inventory.push_front(key3);
        else 
            inventory.push_front(itemIn);
    }
}

/********************************************************************* 
** Description: void Guy::removeInventory(items itemOut)
*               Removes a user specified item from the player inventory
*********************************************************************/
void Guy::removeInventory(items itemOut)
{
    inventory.remove(itemOut);
}

/********************************************************************* 
** Description: int Guy::checkInventorySize()
*               Checks for number of items in inventory
*********************************************************************/
int Guy::checkInventorySize()
{
    return inventory.size();
}

/********************************************************************* 
** Description: void Guy::printInventory()
*               Prints list of inventory items
*********************************************************************/
void Guy::printInventory()
{
    std::cout << " You hold in your inventory:" << std::endl;
    // Using iterators:
    // http://www.cplusplus.com/forum/general/22957/
    if (inventory.empty())
        std::cout << "  You have no items in your inventory! Go find some!" << std::endl;
    else
    {
        std::list<items>::const_iterator iterator = inventory.begin();
        for (int i=1; iterator != inventory.end(); iterator++, i++)
        {
            if (*iterator==sword)
                std::cout << std::setw(3+i) << std::right << i <<". Sword" << std::endl;
            if (*iterator==torch)
                std::cout << std::setw(3+i) << std::right << i <<". Torch" << std::endl;
            if (*iterator==key1)
                std::cout << std::setw(3+i) << std::right << i <<". Main Key" << std::endl;
            if (*iterator==key2)
                std::cout << std::setw(3+i) << std::right << i <<". Black Key Piece" << std::endl;
            if (*iterator==key3)
                std::cout << std::setw(3+i) << std::right << i <<". White Key Piece" << std::endl;
        }
    }
    std::cout << std::endl;
}

/********************************************************************* 
** Description: bool Guy::checkForItem(items checkItem)
*               Checks if a specific item exists in inventory
*********************************************************************/
bool Guy::checkForItem(items checkItem)
{
    std::list<items>::const_iterator iterator = inventory.begin();
    for (; iterator != inventory.end(); iterator++)
    {
        if (*iterator==checkItem)
            return true;
    }
    return false;
}

/********************************************************************* 
** Description: void Guy::dropItem()
*               Drops user specified item from inventory onto map 
*               where it can be picked up again if needed
*********************************************************************/
void Guy::dropItem()
{
    int userIn;
    items toBeDropped;
    if (this->checkInventorySize()>0 && this->getWhereAmINow()->getItemBoard(this->getPositionRow(),this->getPositionCol())==dirt)
    {
        std::cout << "  Which item would you like to drop?" << std::endl;
        printInventory();
        std::cout << "  Please enter the number index of the item:" << std::endl;
        std::cout << "      --> ";
        userIn=inventoryDropValidate(this->checkInventorySize());
        std::cout << std::endl;
        std::list<items>::const_iterator iterator = inventory.begin();
        for (int i=1; i<userIn; i++)
        {
            iterator++;
        }
        toBeDropped=*iterator;
        inventory.remove(*iterator);
        this->getWhereAmINow()->setItemBoard(this->getPositionRow(),this->getPositionCol(), toBeDropped);
    }
    else 
    {
        std::cout << "   Be sure you have something in your inventory or you're not over an item already!" << std::endl << std::endl;
    }
}

/********************************************************************* 
** Description: Get and Set functions
*               The mutator methods are used to control changes to a 
*               Space class member variables. Getter methods return 
*               the value of Space class private member variables.
*********************************************************************/
void Guy::setSteps(int stepsIn)
{
    steps=stepsIn;
}

void Guy::setLimits(int southLimitIn, int eastLimitIn)
{
    southLimit=southLimitIn;
    eastLimit=eastLimitIn;
}

void Guy::setPosition(int rowIn, int colIn)
{
    position[row]=rowIn;
    position[col]=colIn;
}

void Guy::setWhereAmINow(Space* youAreHere)
{
    whereAmINow=youAreHere;
}

int Guy::getEastLimit()
{
    return eastLimit;
}

int Guy::getSouthLimit()
{
    return southLimit;
}

int Guy::getSteps()
{
    return steps;
}

int Guy::getPositionRow()
{
    return position[row];
}

int Guy::getPositionCol()
{
    return position[col];
}

Space* Guy::getWhereAmINow()
{
    return whereAmINow;
}

/********************************************************************* 
** Description: Guy::~Guy()
*               Guy class destructor
*********************************************************************/
Guy::~Guy()
{
    
}