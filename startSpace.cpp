/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the methods and functions required 
*               to use StartSpace class objects. These objects are
*               are the starting position for all players, and include
*               4 doors one for each side.
*********************************************************************/
#include <iostream>
#include "startSpace.hpp"

/********************************************************************* 
** Description: StartSpace::StartSpace()
*               StartSpace default constructor
*********************************************************************/
StartSpace::StartSpace()
{
    setRoomRows(16);
    setRoomCols(16);
    for (int i=0; i<getRoomRows(); i++)
    {
        for (int j=0; j<getRoomCols(); j++)
        {
            boardPtr[i][j]=this;
        }
    }
    unlockedNS=false;
    itemBoard[5][5]=torch;
    itemBoard[3][14]=key1;
    player=NULL;
}

/********************************************************************* 
** Description: void StartSpace::setRoomPtrs()
*               Used by adjacent rooms to set the door pointers in 
*               the StartSpace room. Also configures the players 
*               location when moving into the StartSpace room.
*********************************************************************/
void StartSpace::setRoomPtrs()
{
    player->setLimits(getRoomRows()-1,getRoomCols()-1);
    boardPtr[0][7]=getTop();
    if (player->getPositionCol()==0 && player->getPositionRow()==4)
        boardPtr[7][15]=this->getRightPtr();
    if (player->getPositionCol()==9 && player->getPositionRow()==4)
        boardPtr[7][0]=this->getLeftPtr();
    boardPtr[15][7]=getBottom();
    if (player->checkForItem(key2)==true && player->checkForItem(key3)==true)
    {
        itemBoard[7][7]=keyHole;
    }
}

/********************************************************************* 
** Description: void StartSpace::printRoom()
*               Outputs to consol the room map where the player
*               currently exists.
*********************************************************************/
void StartSpace::printRoom()
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
            else if ((itemBoard[i][j]==key1 || itemBoard[i][j]==key2 || itemBoard[i][j]==key3) && player->checkForItem(torch))
                std::cout << 'K' << " " ;
            else if (itemBoard[i][j]==sword && player->checkForItem(torch))
                std::cout << 'S' << " " ;
            else if (itemBoard[i][j]==keyHole && player->checkForItem(torch))
                std::cout << '#' << " " ;
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
** Description: void StartSpace::detect()
*               Determines if player is near interactive item.
*               Prompts user for input when item is touched.
*********************************************************************/
void StartSpace::detect()
{
    if ((boardPtr[player->getPositionRow()][player->getPositionCol()]!=this))
    {
        std::cout << "   You are in front of a door." << std::endl;
        std::cout << "      A dim sign says: " << boardPtr[player->getPositionRow()][player->getPositionCol()]->getRoomName() << std::endl << std::endl;
        doorEncounter();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (unlockedNS==false) // Player is moving through North or South door for first time
        {
            if (player->checkForItem(key1)==true)
            {
                std::cout << "   Odd. Your pocket feels lighter. The door ahead of you creaked open." << std::endl;
                std::cout << "     An unlocking noise echoes from across the room." << std::endl;
                player->removeInventory(key1);
                unlockedNS=true;
            }
            else
            {
                std::cout << "   What happens when an irresistible force meets an immovable object? The door stays closed unfortunately." << std::endl;
                std::cout << "     It apears this door needs a key." << std::endl << std::endl;
            }
        }
        if (unlockedNS==true && userInput==1)
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
            std::cout << "You choose to remain, one step is taken." << std::endl << std::endl;
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
    
    if (itemBoard[player->getPositionRow()][player->getPositionCol()]==key1)
    {
        keyEncounter();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1&& player->checkInventorySize()<3)
        {
            std::cout << "The key is old and corroded. Maybe it belongs to a door nearby?" << std::endl;
            std::cout << " Your inventory now holds a key!" << std::endl << std::endl;
            player->addInventory(key1);
            itemBoard[player->getPositionRow()][player->getPositionCol()]=dirt;
        }
        else if (userInput==1 && player->checkInventorySize()==3)
            std::cout << "  You need to remove one item from your inventory before you can pick up this item" << std::endl << std::endl;
        else
            std::cout << "The key doesn't seem to mind" << std::endl << std::endl;
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
    
    if (itemBoard[player->getPositionRow()][player->getPositionCol()]==keyHole)
    {
        keyHoleEncounter();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1)
        {
            std::cout << "The feeling of fresh air rushes in." << std::endl;
            std::cout << "  You're finally free!" << std::endl << std::endl;
            player->setSteps(-777);
        }
        else
            std::cout << "Nothing good can come of this." << std::endl << std::endl;
    }
}

/********************************************************************* 
** Description: Get and Set functions
*               The mutator methods are used to control changes to a 
*               Space class member variables. Getter methods return 
*               the value of Space class private member variables.
*********************************************************************/
void StartSpace::setItemBoard(int rowIn, int colIn, items itemDropped)
{
    itemBoard[rowIn][colIn]=itemDropped;
}

items StartSpace::getItemBoard(int rowIn, int colIn)
{
    return itemBoard[rowIn][colIn];
}

void StartSpace::setLeftPtr(Space* leftPtrIn)
{
    leftPtr=leftPtrIn;
}

void StartSpace::setRightPtr(Space* rightPtrIn)
{
    rightPtr=rightPtrIn;
}

void StartSpace::setPlayerPtr(Guy* playerPtr)
{
    player=playerPtr;
}

Space* StartSpace::getLeftPtr()
{
    return leftPtr;
}

Space* StartSpace::getRightPtr()
{
    return rightPtr;
}

Guy* StartSpace::getPlayerPtr()
{
    return player;
}

/********************************************************************* 
** Description: StartSpace::~StartSpace()
*               StartSpace class destructor
*********************************************************************/
StartSpace::~StartSpace()
{
    
}