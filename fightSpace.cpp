/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the methods and functions required 
*               to use FightSpace class objects. These objects are
*               rooms in the game which include a monster that chases
*               the player.
*********************************************************************/
#include "fightSpace.hpp"
#include <iostream>

/********************************************************************* 
** Description: FightSpace::FightSpace()
*               FightSpace class default constructor
*********************************************************************/
FightSpace::FightSpace()
{
    this->setRoomRows(10);
    this->setRoomCols(10);
    for (int i=0; i<this->getRoomRows(); i++)
    {
        for (int j=0; j<this->getRoomCols(); j++)
        {
            boardPtr[i][j]=this;
        }
    }
    monsterLocation[0]=-1;
    monsterLocation[1]=-1;
    player=NULL;
}

/********************************************************************* 
** Description: void FightSpace::setRoomPtrs()
*               Used by adjacent rooms to set the door pointers in 
*               the FIghtSpace room. Also configures the players 
*               location when moving into the FightSpace room.
*********************************************************************/
void FightSpace::setRoomPtrs()
{
    std::cout << "Be quick or be killed. This room contains a fierce monster!" << std::endl;
    // Set the player limits inside the room
    player->setLimits(getRoomRows()-1,getRoomCols()-1);
    // Set the door positions in the room
    boardPtr[0][4]=getTop();
    boardPtr[4][9]=getRight();
    boardPtr[4][0]=getLeft();
    boardPtr[9][4]=getBottom();
}

/********************************************************************* 
** Description: void FightSpace::printRoom()
*               Outputs to consol the room map where the player
*               currently exists.
*********************************************************************/
void FightSpace::printRoom()
{
    std::cout <<" Steps Remaining" << " | Room: " << std::endl;
    std::cout <<"       " << player->getSteps() << "         " << this->getRoomName() << std::endl << std::endl;
    std::cout << "     " << '|' << std::string(getRoomCols()*2,'-') << '|' <<std::endl;
    for (int i=0; i<getRoomRows(); i++)
    {
        std::cout << "     " << '|' ;
        // Multiple items need to be printed. However, several won't appear if player does not have torch
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
            else if (itemBoard[i][j]==monster && player->checkForItem(torch))
                std::cout << 'M' << " " ;
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
** Description: void FightSpace::detect()
*               Determines if player is near interactive item.
*               Prompts user for input when item is touched. 
*********************************************************************/
void FightSpace::detect()
{
    // Identify if a door is present
    // Make sure player location holds pointer not similar to current room and that such a pointer is not NULL
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
            // Need to store original east and south limits for determining future player location
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
    
    // Determine if a monster is nearby and ready to fight
    for (int i=-1; i<2; i++)
    {
        for (int j=-1; j<2; j++)
        {
            if (itemBoard[player->getPositionRow()+i][player->getPositionCol()+j]==monster)
            {
                fight();
            }
        }
    }
    monsterMove();
    
    // Determine if player location is on top of exit keys
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
            itemBoard[monsterLocation[0]][monsterLocation[1]]=dirt;
        }
        else if (userInput==1 && player->checkInventorySize()==3)
            std::cout << "  You need to remove one item from your inventory before you can pick up this item" << std::endl << std::endl;
        else
            std::cout << "The key doesn't seem to mind" << std::endl << std::endl;
    }
    
    // Determine if player location is on top of a torch item
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
    
    // Determine if player location is on top of a word item
    if (itemBoard[player->getPositionRow()][player->getPositionCol()]==sword)
    {
        swordEncounter();
        int userInput;
        userInput=mainMenuValidate();
        std::cout << std::endl;
        if (userInput==1 && player->checkInventorySize()<3)
        {
            std::cout << "  The sword begins to feel heavy. It has been added to your inventory!" << std::endl << std::endl;
            player->addInventory(sword);
            itemBoard[player->getPositionRow()][player->getPositionCol()]=dirt;
        }
        else if (userInput==1 && player->checkInventorySize()==3)
            std::cout << "  You need to remove one item from your inventory before you can pick up this item" << std::endl << std::endl;
        else
            std::cout << " A bright spot remains in the sea of dirt." << std::endl << std::endl;
    }
}

/********************************************************************* 
** Description: void FightSpace::monsterMove()
*               Chase function for monster in room. Will follow player
*               until contact is made, at which point a fight will 
*               start.
*********************************************************************/
void FightSpace::monsterMove()
{
    if (itemBoard[monsterLocation[0]][monsterLocation[1]]==monster)
    {
        int vertDiff, horizDiff;
        vertDiff=(player->getPositionRow()-monsterLocation[0]);
        horizDiff=(player->getPositionCol()-monsterLocation[1]);
        if (vertDiff!=1 || vertDiff!=-1)
        {
            if (vertDiff<-1)
            {
                itemBoard[monsterLocation[0]][monsterLocation[1]]=dirt;
                itemBoard[monsterLocation[0]-=1][monsterLocation[1]]=monster;
            }
            if (vertDiff>1)
            {
                itemBoard[monsterLocation[0]][monsterLocation[1]]=dirt;
                itemBoard[monsterLocation[0]+=1][monsterLocation[1]]=monster;
            }
        }
        if (horizDiff!=1 || horizDiff!=-1)
        {
            if (horizDiff<-1)
            {
                itemBoard[monsterLocation[0]][monsterLocation[1]]=dirt;
                itemBoard[monsterLocation[0]][monsterLocation[1]-=1]=monster;
            }
            if (horizDiff>1)
            {
                itemBoard[monsterLocation[0]][monsterLocation[1]]=dirt;
                itemBoard[monsterLocation[0]][monsterLocation[1]+=1]=monster;
            }
        }
    }
}

/********************************************************************* 
** Description: void FightSpace::fight()
*               A generic game of rock, paper, scissors. Monster
*               actions are randomly generated
*********************************************************************/
void FightSpace::fight()
{
    enum weapons {rock, paper, scissors};
    int weaponOfChoice, enemyWeapon;
    enemyWeapon=(randomGenerator()*3);
    monsterEncounter();
    //  If player has picked up a sword then the battle is omitted for a one shot kill
    if (player->checkForItem(sword)==true)
    {
        std::cout << "A quick slash with your sword." << std::endl;
        std::cout << "   How lucky you had a sword!" << std::endl << std::endl;
        itemBoard[monsterLocation[0]][monsterLocation[1]]=key2;
    }
    else
    {
        std::cin >> weaponOfChoice;
        switch (weaponOfChoice)
        {
            case 1:
            if (enemyWeapon==rock)
            {
                std::cout << "   It's a tie! Both you and the monster are injured from the explosive conflict!" << std::endl;
                player->setSteps(player->getSteps()-10);
            }
            else if (enemyWeapon==paper)
            {
                std::cout << "   The monster strikes hard! You stumble back from the sheer amount of power!" << std::endl;
                player->setSteps(player->getSteps()-50);
            }
            else
            {
                std::cout << "   Your arm motion is impeccable, your tactics unyielding, and your fearlessness known. The monster is killed in one fell swoop!" << std::endl;
                itemBoard[monsterLocation[0]][monsterLocation[1]]=key2;
            }
            break;
            case 2:
            if (enemyWeapon==paper)
            {
                std::cout << "   It's a tie! Both you and the monster are injured from the explosive conflict!" << std::endl;
                player->setSteps(player->getSteps()-10);
            }
            else if (enemyWeapon==scissors)
            {
                std::cout << "   The monster strikes hard! You stumble back from the sheer amount of power!" << std::endl;
                player->setSteps(player->getSteps()-50);
            }
            else
            {
                std::cout << "   Your arm motion is impeccable, your tactics unyielding, and your fearlessness known. The monster is killed in one fell swoop!" << std::endl;
                itemBoard[monsterLocation[0]][monsterLocation[1]]=key2;
            }
            break;
            case 3:
            if (enemyWeapon==scissors)
            {
                std::cout << "   It's a tie! Both you and the monster are injured from the explosive conflict!" << std::endl;
                player->setSteps(player->getSteps()-10);
            }
            else if (enemyWeapon==rock)
            {
                std::cout << "   The monster strikes hard! You stumble back from the sheer amount of power!" << std::endl;
                player->setSteps(player->getSteps()-50);
            }
            else
            {
                std::cout << "   Your motion is impeccable, your tactics unyielding, and your fearlessness known. The monster is killed in one fell swoop!" << std::endl;
                itemBoard[monsterLocation[0]][monsterLocation[1]]=key2;
            }
            break;
            case 4:
            std::cout << "   Aww shucks :]" << std::endl;
            break;
        }
    }
}

/********************************************************************* 
** Description: Get and Set functions
*               The mutator methods are used to control changes to a 
*               Space class member variables. Getter methods return 
*               the value of Space class private member variables.
*********************************************************************/
void FightSpace::setItems(int rowIn, int colIn)
{
    // This function specifically sets the monster location
    itemBoard[rowIn][colIn]=monster;
    monsterLocation[0]=rowIn;
    monsterLocation[1]=colIn;
}

void FightSpace::setItemBoard(int rowIn, int colIn, items itemDropped)
{
    itemBoard[rowIn][colIn]=itemDropped;
}

items FightSpace::getItemBoard(int rowIn, int colIn)
{
    return itemBoard[rowIn][colIn];
}

void FightSpace::setPlayerPtr(Guy* playerPtr)
{
    player=playerPtr;
}

int FightSpace::getMonsterRow()
{
    return monsterLocation[0];
}

int FightSpace::getMonsterCol()
{
    return monsterLocation[1];
}

/********************************************************************* 
** Description: FightSpace::~FightSpace()
*               FighTSpace class destructor
*********************************************************************/
FightSpace::~FightSpace()
{
    
}