/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the prototypes and interfaces 
*               required to interact with Space class objects.
*               Additional enumeration is defined for inventory list
*               items used in the game.
*********************************************************************/
#ifndef SPACE_HPP
#define SPACE_HPP
#include <string>

// Enumerated items will be used for inventory purposes
enum items {dirt, torch, warp, chest, key1, key2, key3, hole, sword, mimic, heal, monster, keyHole};

class Space
{
private:

    Space *top, *right, *bottom, *left; // 4 required pointers
    int roomRows, roomCols;
    std::string roomName;

public:

    Space();
    virtual void printRoom() = 0; // Prints individual room
    virtual void detect() = 0; // Allows unique detection functions in each room
    virtual void setRoomPtrs() = 0; // Updates room pointers given certain events through game
    virtual void setItemBoard(int, int, items) = 0; // Each room requires individual attention to its items
    virtual items getItemBoard(int, int) = 0; // Retrieving items mirrors setting items for each room
    double randomGenerator();
    void setTop(Space*);
    void setRight(Space*);
    void setBottom(Space*);
    void setLeft(Space*);
    void setRoomRows(int);
    void setRoomCols(int);
    void setRoomName(std::string);
    void setDoors(Space*, Space*, Space*, Space*);
    Space* getTop();
    Space* getRight();
    Space* getBottom();
    Space* getLeft();
    int getRoomRows();
    int getRoomCols();
    std::string getRoomName();
    virtual ~Space();

};

#endif