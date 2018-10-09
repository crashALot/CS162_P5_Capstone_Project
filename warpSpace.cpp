/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the methods and functions required 
*               to use WarpSpace class objects. These objects are
*               rooms in the game which include a warp item that can
*               transport a player to any room in the game.
*********************************************************************/
#include "warpSpace.hpp"
#include <iostream>

/********************************************************************* 
** Description: WarpSpace::WarpSpace()
*               WarpSpace class default constructor
*********************************************************************/
WarpSpace::WarpSpace()
{
    this->setRoomRows(24);
    this->setRoomCols(10);
    for (int i=0; i<this->getRoomRows(); i++)
    {
        for (int j=0; j<this->getRoomCols(); j++)
        {
            boardPtr[i][j]=this;
        }
    }
    player=NULL;
    spaceArrayPtr=NULL;
}

/********************************************************************* 
** Description: void WarpSpace::setRoomPtrs()
*               Used by adjacent rooms to set the door pointers in 
*               the WarpSpace room. Also configures the players 
*               location when moving into the WarpSpace room.
*********************************************************************/
void WarpSpace::setRoomPtrs()
{
    player->setLimits(getRoomRows()-1,getRoomCols()-1);
    boardPtr[0][4]=getTop();
    boardPtr[11][9]=getRight();
    boardPtr[11][0]=getLeft();
    boardPtr[23][4]=getBottom();
}

/********************************************************************* 
** Description: void WarpSpace::printRoom()
*               Outputs to consol the room map where the player
*               currently exists.
*********************************************************************/
void WarpSpace::printRoom()
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
            else if (itemBoard[i][j]==warp && player->checkForItem(torch))
                std::cout << 'W' << " " ;
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
** Description: void WarpSpace::detect()
*               Determines if player is near interactive item.
*               Prompts user for input when item is touched. 
*********************************************************************/
void WarpSpace::detect()
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
            //std::cout << "Current player row is: " << player->getPositionRow() << " and col " << player->getPositionCol() << std::endl;
            //std::cout << "Current east limit is " << player->getEastLimit() << std::endl;
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
    if (itemBoard[player->getPositionRow()][player->getPositionCol()]==warp)
    {
        warpEncounter();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1)
        {
            int randomLocation;
            randomLocation=randomGenerator()*5;
            switch (randomLocation)
            {
                case 0:
                    player->setWhereAmINow(spaceArrayPtr[0]);
                    std::cout<< "You are headed on a magical trip to room: " << spaceArrayPtr[0]->getRoomName() << std::endl << std::endl;
                    player->getWhereAmINow()->setRoomPtrs();
                    player->setPosition(randomGenerator()*(player->getWhereAmINow()->getRoomRows()), randomGenerator()*(player->getWhereAmINow()->getRoomCols()));
                    break;
                
                case 1:
                    player->setWhereAmINow(spaceArrayPtr[1]);
                    std::cout<< "You are headed on a magical trip to room: " << spaceArrayPtr[1]->getRoomName() << std::endl << std::endl;
                    player->getWhereAmINow()->setRoomPtrs();
                    player->setPosition(randomGenerator()*(player->getWhereAmINow()->getRoomRows()), randomGenerator()*(player->getWhereAmINow()->getRoomCols()));
                    break;
                
                case 2:
                    player->setWhereAmINow(spaceArrayPtr[2]);
                    std::cout<< "You are headed on a magical trip to room: " << spaceArrayPtr[2]->getRoomName() << std::endl << std::endl;
                    player->getWhereAmINow()->setRoomPtrs();
                    player->setPosition(randomGenerator()*(player->getWhereAmINow()->getRoomRows()), randomGenerator()*(player->getWhereAmINow()->getRoomCols()));
                    break;
                
                case 3:
                    player->setWhereAmINow(spaceArrayPtr[3]);
                    std::cout<< "You are headed on a magical trip to room: " << spaceArrayPtr[3]->getRoomName() << std::endl << std::endl;
                    player->getWhereAmINow()->setRoomPtrs();
                    player->setPosition(randomGenerator()*(player->getWhereAmINow()->getRoomRows()), randomGenerator()*(player->getWhereAmINow()->getRoomCols()));
                    break;
                
                case 4:
                    player->setWhereAmINow(spaceArrayPtr[4]);
                    std::cout<< "You are headed on a magical trip to room: " << spaceArrayPtr[4]->getRoomName() << std::endl << std::endl;
                    player->getWhereAmINow()->setRoomPtrs();
                    player->setPosition(randomGenerator()*(player->getWhereAmINow()->getRoomRows()), randomGenerator()*(player->getWhereAmINow()->getRoomCols()));
                    break;
            }
        }
        else
            std::cout << "Chance isn't needed right now." << std::endl;
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
void WarpSpace::setItems(int rowIn, int colIn)
{
    itemBoard[rowIn][colIn]=warp;
}

void WarpSpace::setSpacePtrs(Space** spaceArrayIn)
{
    spaceArrayPtr=spaceArrayIn;
}

void WarpSpace::setItemBoard(int rowIn, int colIn, items itemDropped)
{
    itemBoard[rowIn][colIn]=itemDropped;
}

items WarpSpace::getItemBoard(int rowIn, int colIn)
{
    return itemBoard[rowIn][colIn];
}

void WarpSpace::setPlayerPtr(Guy* playerPtr)
{
    player=playerPtr;
}

/********************************************************************* 
** Description: WarpSpace::~WarpSpace()
*               WarpSpace class destructor
*********************************************************************/
WarpSpace::~WarpSpace()
{
    
}