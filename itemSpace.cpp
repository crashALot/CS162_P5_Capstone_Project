/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the methods and functions required 
*               to use ItemSpace class objects. These objects are
*               rooms in the game which include multiple chests for
*               the user to open.
*********************************************************************/
#include "itemSpace.hpp"
#include <iostream>

/********************************************************************* 
** Description: ItemSpace::ItemSpace()
*               ItemSpace defualt constructor
*********************************************************************/
ItemSpace::ItemSpace()
{
    this->setRoomRows(20);
    this->setRoomCols(20);
    for (int i=0; i<this->getRoomRows(); i++)
    {
        for (int j=0; j<this->getRoomCols(); j++)
        {
            boardPtr[i][j]=this;
        }
    }
    itemList[0]='s';
    itemList[1]='h';
    itemList[2]='m';
    itemList[3]='h';
    itemList[4]='m';
    itemList[5]='m';
    player=NULL;
}

/********************************************************************* 
** Description: void ItemSpace::setRoomPtrs()
*               Used by adjacent rooms to set the door pointers in 
*               the ItemSpace room. Also configures the players 
*               location when moving into the ItemSpace room.
*********************************************************************/
void ItemSpace::setRoomPtrs()
{
    player->setLimits(getRoomRows()-1,getRoomCols()-1);
    boardPtr[0][9]=getTop();
    boardPtr[9][19]=getRight();
    boardPtr[9][0]=getLeft();
    boardPtr[19][9]=getBottom();
}

/********************************************************************* 
** Description: void ItemSpace::printRoom()
*               Outputs to consol the room map where the player
*               currently exists.   
*********************************************************************/
void ItemSpace::printRoom()
{
    std::cout <<" Steps Remaining" << " | Room: " << std::endl;
    std::cout <<"       " << player->getSteps() << "         " << this->getRoomName() << std::endl << std::endl;
    std::cout << "     " << '|' << std::string(getRoomCols()*2,'-') << '|' <<std::endl;
    for (int i=0; i<getRoomRows(); i++)
    {
        std::cout << "     " << '|' ;
        for (int j=0; j<getRoomCols(); j++)
        {
            if (i==player->getPositionRow() && j == player->getPositionCol())
                std::cout << 'X' << " ";
            else if (boardPtr[i][j]!=this && boardPtr[i][j]!=NULL && player->checkForItem(torch))
                std::cout << 'D' << " ";
            else if (itemBoard[i][j]==torch)
                std::cout << 'T' << " " ;
            else if ((itemBoard[i][j]==key2 || itemBoard[i][j]==key3) && player->checkForItem(torch))
                std::cout << 'K' << " " ;
            else if (itemBoard[i][j]==chest && player->checkForItem(torch))
                std::cout << '$' << " " ;
            else if (itemBoard[i][j]==sword && player->checkForItem(torch))
                std::cout << 'S' << " " ;
            else
                std::cout <<  "  ";
            if (j==getRoomCols()-1)
                std::cout << '|';
        }
        std::cout << std::endl;
    }
    std::cout << "     " << '|' << std::string(getRoomCols()*2,'-') << '|' <<std::endl;
}

/********************************************************************* 
** Description: void ItemSpace::detect()
*               Determines if player is near interactive item.
*               Prompts user for input when item is touched.
*********************************************************************/
void ItemSpace::detect()
{
    if (boardPtr[player->getPositionRow()][player->getPositionCol()]!=this && boardPtr[player->getPositionRow()][player->getPositionCol()]!=NULL)
    {
        std::cout << "   You are in front of a door. Would you like to open it?" << std::endl;
        std::cout << "      The door will take you to: " << boardPtr[player->getPositionRow()][player->getPositionCol()]->getRoomName() << std::endl << std::endl;
        doorEncounter();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1)
        {
            int oldRowLimit = player->getSouthLimit();
            int oldColLimit= player->getEastLimit();
            player->setWhereAmINow(boardPtr[player->getPositionRow()][player->getPositionCol()]);
            player->getWhereAmINow()->setRoomPtrs();
            if (player->getPositionRow()==oldRowLimit) // Player is moving through South door
            {
                player->setPosition(1, (player->getEastLimit())/2);
            }
            if (player->getPositionCol()==oldColLimit) // Player is moving through East door
            {
                player->setPosition((player->getSouthLimit())/2,1);
            }
            if (player->getPositionRow()==0) // Player is moving through North door
            {
                player->setPosition(player->getSouthLimit()-1,(player->getEastLimit())/2);
            }
            if (player->getPositionCol()==0) // Player is moving through West door
            {
                player->setPosition(player->getSouthLimit()/2,player->getEastLimit()-1);
            }
        }
        else
            std::cout << "   You choose to remain, one step is taken." << std::endl << std::endl;
    }
    
    if (itemBoard[player->getPositionRow()][player->getPositionCol()]==chest)
    {
        chestEncounter();
        int itemSelection, userInput, counts=6;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1)
        {
            itemSelection=(randomGenerator()*counts);
            switch (itemList[itemSelection])
            {
                case 's':
                swordEncounter();
                userInput=mainMenuValidate();
                std::cout << std::endl;
                if (userInput==1 && player->checkInventorySize()<3)
                {
                    std::cout << "   You're more formidable than before! The sword has been added to your inventory!" <<std::endl;
                    player->addInventory(sword);
                    itemList[itemSelection]='h';
                }
                else if (userInput==1 && player->checkInventorySize()==3)
                    std::cout << "  You need to remove one item from your inventory before you can pick up this item" << std::endl << std::endl;
                else
                    std::cout <<"   The seemingly sturdy sword turns to dust in your hands. A strange occurence." << std::endl << std::endl;
                break;
                
                case 'h':
                healEncounter();
                player->setSteps(player->getSteps()+50);
                itemList[itemSelection]='m';
                break;
                
                case 'm':
                mimicEncounter();
                player->setSteps(player->getSteps()-20);
                itemList[itemSelection]='h';
                break;
            }
        itemBoard[player->getPositionRow()][player->getPositionCol()]=dirt;
        }
        else
            std::cout << "   The chest is unmoved." << std::endl;
    }
    
    if (itemBoard[player->getPositionRow()][player->getPositionCol()]==torch)
    {
        torchEncounter();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1 && player->checkInventorySize()<3)
        {
            std::cout << "The torch illuminates your way, it is added to your inventory!" << std::endl << std::endl;
            player->addInventory(torch);
            itemBoard[player->getPositionRow()][player->getPositionCol()]=dirt;
        }
        else if (userInput==1 && player->checkInventorySize()==3)
            std::cout << "  You need to remove one item from your inventory before you can pick up this item" << std::endl << std::endl;
        else
            std::cout << "The torch flickers quietly" << std::endl << std::endl;
    }
    
    if (itemBoard[player->getPositionRow()][player->getPositionCol()]==key2 || itemBoard[player->getPositionRow()][player->getPositionCol()]==key3)
    {
        keyEncounterMonster();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1 && player->checkInventorySize()<3)
        {
            std::cout << "You remember an old friend named Key, he opened doors too." << std::endl;
            std::cout << " Your inventory now holds a key!" << std::endl << std::endl;
            player->addInventory(key2);
            itemBoard[player->getPositionRow()][player->getPositionCol()]=dirt;
        }
        else if (userInput==1 && player->checkInventorySize()==3)
            std::cout << "  You need to remove one item from your inventory before you can pick up this item" << std::endl << std::endl;
        else
            std::cout << "The key doesn't seem to mind" << std::endl << std::endl;
    }
    
    if (itemBoard[player->getPositionRow()][player->getPositionCol()]==sword)
    {
        swordEncounter();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1 && player->checkInventorySize()<3)
        {
            std::cout << "The sword begins to feel heavy. It has been added to your inventory!" << std::endl << std::endl;
            player->addInventory(sword);
            itemBoard[player->getPositionRow()][player->getPositionCol()]=dirt;
        }
        else if (userInput==1 && player->checkInventorySize()==3)
            std::cout << "  You need to remove one item from your inventory before you can pick up this item" << std::endl << std::endl;
        else
            std::cout << "A bright spot in the sea of dirt." << std::endl << std::endl;
    }
}

/********************************************************************* 
** Description: Get and Set functions
*               The mutator methods are used to control changes to a 
*               Space class member variables. Getter methods return 
*               the value of Space class private member variables.
*********************************************************************/
void ItemSpace::setItems(int rowIn, int colIn)
{
    itemBoard[rowIn][colIn]=chest;
}

void ItemSpace::setItemBoard(int rowIn, int colIn, items itemDropped)
{
    itemBoard[rowIn][colIn]=itemDropped;
}

items ItemSpace::getItemBoard(int rowIn, int colIn)
{
    return itemBoard[rowIn][colIn];
}

void ItemSpace::setPlayerPtr(Guy* playerPtr)
{
    player=playerPtr;
}

/********************************************************************* 
** Description: ItemSpace::~ItemSpace()
*               ItemSpace destructor
*********************************************************************/
ItemSpace::~ItemSpace()
{
    
}