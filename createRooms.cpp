/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the methods and functions required 
*               to use CreateRooms class objects. These objects 
*               instantiate individual rooms and configure their
*               layout as appropriate for their position on the map.
*********************************************************************/
#include "createRooms.hpp"
#include <iostream>

/********************************************************************* 
** Description: CreateRooms::CreateRooms()
*               CreateRooms default constructor
*********************************************************************/
CreateRooms::CreateRooms()
{
    centerPtr=new StartSpace();
    centerPtr->setRoomName("Center Room");
    topPtr=new ItemSpace();
    topPtr->setRoomName("Top Item Room");
    bottomPtr=new ItemSpace();
    bottomPtr->setRoomName("Bottom Item Room");
    topRightPtr=new WarpSpace();
    topRightPtr->setRoomName("Top Right Warp Space");
    bottomLeftPtr=new WarpSpace();
    bottomLeftPtr->setRoomName("Bottom Left Warp Space");
    rightPtr=new FightSpace();
    rightPtr->setRoomName("Might Makes Right");
    leftPtr=new FightSpace();
    leftPtr->setRoomName("Left For Grabs");
    
    centerPtr->setDoors(topPtr, NULL, bottomPtr, NULL);
    centerPtr->setLeftPtr(leftPtr);
    centerPtr->setRightPtr(rightPtr);
    topPtr->setDoors(NULL, topRightPtr, centerPtr, NULL);
    bottomPtr->setDoors(centerPtr, NULL, NULL, bottomLeftPtr);
    topRightPtr->setDoors(NULL, NULL, rightPtr, topPtr);
    bottomLeftPtr->setDoors(leftPtr, bottomPtr, NULL, NULL);
    rightPtr->setDoors(topRightPtr, NULL, NULL, centerPtr);
    leftPtr->setDoors(NULL, centerPtr, bottomLeftPtr, NULL);
    
    topPtr->setItems(2,7);
    topPtr->setItems(16,12);
    topPtr->setItems(14,4);
    bottomPtr->setItems(15,19);
    bottomPtr->setItems(10,3);
    bottomPtr->setItems(6,18);
    topRightPtr->setItems(11,3);
    bottomLeftPtr->setItems(11,7);
    
    this->createSpaceArray();
    topRightPtr->setSpacePtrs(getSpaceArray());
    bottomLeftPtr->setSpacePtrs(getSpaceArray());
    
    leftPtr->setItems(9,9);
    rightPtr->setItems(0,0);
}

/********************************************************************* 
** Description: Get and Set functions
*               The mutator methods are used to control changes to a 
*               Space class member variables. Getter methods return 
*               the value of Space class private member variables.
*********************************************************************/
void CreateRooms::setPlayerPtr(Guy* playerPtrIn)
{
    centerPtr->setPlayerPtr(playerPtrIn);
    topPtr->setPlayerPtr(playerPtrIn);
    bottomPtr->setPlayerPtr(playerPtrIn);
    topRightPtr->setPlayerPtr(playerPtrIn);
    bottomLeftPtr->setPlayerPtr(playerPtrIn);
    rightPtr->setPlayerPtr(playerPtrIn);
    leftPtr->setPlayerPtr(playerPtrIn);
}

ItemSpace* CreateRooms::getTopPtr()
{
    return topPtr;
}

ItemSpace* CreateRooms::getBottomPtr()
{
    return bottomPtr;
}

FightSpace* CreateRooms::getRightPtr()
{
    return rightPtr;
}

FightSpace* CreateRooms::getLeftPtr()
{
    return leftPtr;
}

WarpSpace* CreateRooms::getTopRightPtr()
{
    return topRightPtr;
}

WarpSpace* CreateRooms::getBottomLeftPtr()
{
    return bottomLeftPtr;
}

StartSpace* CreateRooms::getCenterPtr()
{
    return centerPtr;
}

Space** CreateRooms::getSpaceArray()
{
    return spaceArray;
}

/********************************************************************* 
** Description: void CreateRooms::createSpaceArray()
*               An array is created with pointers to each individual 
*               room. This array can be passed to different class
*               objects as a gateway to other room functions
*********************************************************************/
void CreateRooms::createSpaceArray()
{
    spaceArray[0]=centerPtr;
    spaceArray[1]=topPtr;
    spaceArray[2]=bottomPtr;
    spaceArray[3]=leftPtr;
    spaceArray[4]=rightPtr;
}

/********************************************************************* 
** Description: CreateRooms::~CreateRooms()
*               CreateRooms class destructor
*********************************************************************/
CreateRooms::~CreateRooms()
{
    delete centerPtr;
    delete topPtr;
    delete bottomPtr;
    delete topRightPtr;
    delete bottomLeftPtr;
    delete rightPtr;
    delete leftPtr;
}
