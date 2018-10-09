/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the initial menu and exit prompts 
*               needed for gameplay. Additional coordination is
*               contained here to move the player around the game 
*               boards.
*********************************************************************/
#include <iostream>
#include "spaceMenu.hpp"

/********************************************************************* 
** Description: SpaceMenu::SpaceMenu(CreateRooms* newMapIn)
*               SpaceMenu class default constructor. Uses CreateRooms
*               object as reference when creating new player
*               character
*********************************************************************/
SpaceMenu::SpaceMenu(CreateRooms* newMapIn)
{
    roomPtr=newMapIn;
    player=new Guy();
    spacePtr=NULL;
}

/********************************************************************* 
** Description: void SpaceMenu::mainMenu()
*               Prompts user to play a new game or exit program.
*********************************************************************/
int SpaceMenu::mainMenu()
{
        int userChoice;
        std::cout << std::endl;
        std::cout << "   ****************** Welcome to Run For Your Life! ******************" << std::endl;
        std::cout << std::endl << "             Would you like to: " << std::endl;
        std::cout << "                  1. Play a game" << std::endl;
        std::cout << "                   2. Quit the program" << std::endl; 
        std::cout << "              --> ";
        userChoice=mainMenuValidate();
        std::cout << std::endl;
        if (userChoice==1)
        {
            playGame();
        }
        else
        {
            return 0;
        }
        std::cout << std::endl;
        return 1;
}

/********************************************************************* 
** Description: void SpaceMenu::playGame()
*               Introduces user to gameplay. Prompts user to enter
*               input for character movement and action. Exits game when
*               player dies.
*********************************************************************/
void SpaceMenu::playGame()
{
    instructions();
    introNarrative();
    // Establish initial player room and location in room
    player->setWhereAmINow(roomPtr->getCenterPtr());
    player->setPosition(7,7);
    roomPtr->setPlayerPtr(player);
    player->getWhereAmINow()->setRoomPtrs();
    
    char userDirection;
    while (player->getSteps()>0)
    {
        player->getWhereAmINow()->printRoom();
        std::cout << "  What direction or action would you like to take?" << std::endl;
        std::cout << "   --> ";
        userDirection=playerActionValidate();
        std::cout << std::endl;
        player->action(userDirection);
        player->getWhereAmINow()->detect();
    }
    
    // Exit conditions are based on specific step counts on exit
    if (player->getSteps()==-123)
        std::cout << "  You have exited the game." << std::endl;
    else if (player->getSteps()==-777)
        std::cout << "   What will you do with your freedom?" << std::endl;
    else
    {
        std::cout << std::endl << "   You have succumbed to the poison and quickly lose consciousness." << std::endl;
        std::cout << "     Another lost soul to wander the rooms for eternity! " << std::endl;
    }
}

/********************************************************************* 
** Description: void SpaceMenu::exitMenu()
*               Creates exit message when user leaves game.
*********************************************************************/
int SpaceMenu::exitMenu()
{
        std::cout << "             Would you like to: " << std::endl;
        std::cout << "                  1. Play another game" << std::endl;
        std::cout << "                   2. Exit the program" << std::endl; 
        std::cout << "              --> ";
        int userChoice;
        userChoice=mainMenuValidate();
        std::cout << std::endl;
        if (userChoice==1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
        std::cout << std::endl;
}

/********************************************************************* 
** Description: Get and Set functions
*               The mutator methods are used to control changes to a 
*               Space class member variables. Getter methods return 
*               the value of Space class private member variables.   
*********************************************************************/
Guy* SpaceMenu::getPlayerPtr()
{
    std::cout << player << std::endl;
    return player;
}

CreateRooms* SpaceMenu::getRoomPtr()
{
    return roomPtr;
}

/********************************************************************* 
** Description: SpaceMenu::~SpaceMenu()
*               SpaceMenu class destructor
*********************************************************************/
SpaceMenu::~SpaceMenu()
{
    delete player;
}