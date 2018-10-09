/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the methods and functions required
*               instantiate Space class objects. The space Class is
*               a base class to multiple derived object classes, and
*               utilizes polymorphism to delegate functional duties
*               between classes. There are several purely virtual
*               functions associated with this class.
*********************************************************************/
#include "space.hpp"
#include "spaceMenu.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

/********************************************************************* 
** Description: Space::Space()
*               Space class default constructor.
*********************************************************************/
Space::Space()
{
    top=NULL;
    right=NULL;
    bottom=NULL;
    left=NULL;
    roomRows=-1;
    roomCols=-1;
    std::string roomName="EMPTY";
}

/********************************************************************* 
** Description: double Space::randomGenerator()
*               Produces a random value between 0 and 1.
*********************************************************************/
double Space::randomGenerator()
{
    return static_cast<double>(rand())/(static_cast<double>(RAND_MAX));
}

/********************************************************************* 
** Description: Get and Set functions
*               The mutator methods are used to control changes to a 
*               Space class member variables. Getter methods return 
*               the value of Space class private member variables.
*********************************************************************/
void Space::setTop(Space* topIn)
{
    top=topIn;
}

void Space::setRight(Space* rightIn)
{
    right=rightIn;
}

void Space::setBottom(Space* bottomIn)
{
 bottom=bottomIn;   
}

void Space::setLeft(Space* leftIn)
{
    left=leftIn;
}

void Space::setRoomRows(int rowsIn)
{
    roomRows=rowsIn;
}

void Space::setRoomCols(int colsIn)
{
    roomCols=colsIn;
}

void Space::setRoomName(std::string nameIn)
{
    roomName=nameIn;
}

// Room pointers are set to "doors" in the creatRooms.cpp file
void Space::setDoors(Space* door1, Space* door2, Space* door3, Space* door4)
{
    top=door1;
    right=door2;
    bottom=door3;
    left=door4;
}

Space* Space::getTop()
{
    return top;
}

Space* Space::getRight()
{
    return right;
}

Space* Space::getBottom()
{
    return bottom;
}

Space* Space::getLeft()
{
    return left;
}

int Space::getRoomRows()
{
    return roomRows;
}

int Space::getRoomCols()
{
    return roomCols;
}

std::string Space::getRoomName()
{
    return roomName;
}

/********************************************************************* 
** Description: Space::~Space()
*               Space class destructor
*********************************************************************/
Space::~Space()
{
    
}