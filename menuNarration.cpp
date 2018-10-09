/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: This file contains the methods and functions required 
*               to use the menuNarration.cpp file. This file contains
*               several chunks of text used throughout the game when
*               the player encounters specific events or items.
*********************************************************************/
#include "menuNarration.hpp"
#include <iostream>
#include <iomanip>

/********************************************************************* 
** Description: void introNarrative()
*               
*********************************************************************/
void introNarrative()
{
    std::cout << "    -       You wake up in a cold and dimly lit room. A torch is the only source of light.      -" << std::endl;
    std::cout << "    -     A sharp pungent smell begins to fill the room.                                        -" << std::endl;
    std::cout << "    -   An ominous voice booms out:                                                             -" << std::endl;
    std::cout << "      You are slowly being poisoned. You can only survive if you find the keys to your freedom." << std::endl;
    std::cout << "        You currently stand in the center room." << std::endl;
    std::cout << "          There remain 6 rooms for you to explore and find the keys." << std::endl;
    std::cout << "            However, each step you take is one step closer to your death." << std::endl;
    std::cout << "              Choose carefully where you move." << std::endl;
    std::cout << "                Some rooms hold enemies, while others offer benefits." << std::endl;
    std::cout << "                  Good luck, and good bye." << std::endl<< std::endl;
}

/********************************************************************* 
** Description: void instructions()
*               
*********************************************************************/
void instructions()
{
    std::cout << "    *********************************************************************************************" << std::endl;
    std::cout << "    *--------------------------------------Instructions-----------------------------------------*" << std::endl;
    std::cout << "    * 1. Your goal is to find the two keys which unlock the exit door.                          *" << std::endl;
    std::cout << "    * 2. You only have 200 steps to find the key pieces.                                        *" << std::endl;
    std::cout << "    * 3. Opening chests incurs a risk. You may find a helpful item like a sword or an enemy!    *" << std::endl;
    std::cout << "    * 4. Some doors only appear after a specific sequence of events.                            *" << std::endl;
    std::cout << "    * 5. Your inventory only holds 3 items. Be sure to choose them carefully!                   *" << std::endl;
    std::cout << "    * 6. You are represented by the character 'X'                                               *" << std::endl;
    std::cout << "    * 7. You can use the following characters to perform an action:                             *" << std::endl;
    std::cout << "    *                                                                                           *" << std::endl;
    std::cout << "    *     - n - Moves your character North one step                                             *" << std::endl;
    std::cout << "    *     - e - Moves your character East one step                                              *" << std::endl;
    std::cout << "    *     - s - Moves your character South one step                                             *" << std::endl;
    std::cout << "    *     - w - Moves your character West one step                                              *" << std::endl;
    std::cout << "    *     - i - Prints these instructions for reference                                         *" << std::endl;
    std::cout << "    *     - d - Drops an item from your inventory                                               *" << std::endl;
    std::cout << "    *     - p - Displays your inventory for review                                              *" << std::endl;
    std::cout << "    *     - x - Exits the game                                                                  *" << std::endl;
    std::cout << "    *                                                                                           *" << std::endl;
    std::cout << "    *    Hint: You can enter multiple characters to speed up your travels (eg. nnnsw)           *" << std::endl;
    std::cout << "    *---------------------------------------Good luck!------------------------------------------*" << std::endl;
    std::cout << "    *********************************************************************************************" << std::endl << std::endl;
}

/********************************************************************* 
** Description: void doorEncounter()
*               
*********************************************************************/
void doorEncounter()
{
    std::cout << "   Please enter your choice below:" << std::endl;
    std::cout << "        1. Open the door" << std::endl;
    std::cout << "          2. Remain where you are" << std::endl;
    std::cout << "   --> ";
}

/********************************************************************* 
** Description: void torchEncounter()
*               
*********************************************************************/
void torchEncounter()
{
    std::cout << "You stand over the burning torch. Will you take it?" << std::endl;
    std::cout << "   Please enter your choice below:" << std::endl;
    std::cout << "        1. Take the torch" << std::endl;
    std::cout << "          2. Leave it alone" << std::endl;
    std::cout << "   --> ";
}

/********************************************************************* 
** Description: void keyEncounter()
*               
*********************************************************************/
void keyEncounter()
{
    std::cout << "You hear a jingle and notice a small glint on the ground. A key perhaps?" << std::endl;
    std::cout << "   Please enter your choice below:" << std::endl;
    std::cout << "        1. Pick up the key" << std::endl;
    std::cout << "          2. Leave it alone" << std::endl;
    std::cout << "   --> ";
}

/********************************************************************* 
** Description: void chestEncounter()
*               
*********************************************************************/
void chestEncounter()
{
    std::cout << "A chest, covered in dust, may contain somethings useful." << std::endl;
    std::cout << "   Please enter your choice below:" << std::endl;
    std::cout << "        1. Open the chest" << std::endl;
    std::cout << "          2. Leave it alone" << std::endl;
    std::cout << "   --> ";
}

/********************************************************************* 
** Description: void swordEncounter()
*               
*********************************************************************/
void swordEncounter()
{
    std::cout << "You find the razor sharp sword. Metal amidst dirt." << std::endl;
    std::cout << "   Please enter your choice below:" << std::endl;
    std::cout << "        1. Keep the sword" << std::endl;
    std::cout << "          2. Leave it alone" << std::endl;
    std::cout << "   --> ";
}

/********************************************************************* 
** Description: void healEncounter()
*               
*********************************************************************/
void healEncounter()
{
    std::cout << "A glowing green potion illuminates the chest. You can make out some illegible ingredients on the label." << std::endl;
    std::cout << "   You drink it in desperation. The feeling of rejuvenation is unexpected! A second wind!" << std::endl;
}

/********************************************************************* 
** Description: void mimicEncounter()
*               
*********************************************************************/
void mimicEncounter()
{
    std::cout << "A vicious rumble followed by a painful attack! Some kind of living box?" << std::endl;
    std::cout << " The attack leaves you shaken and weakened. You can no longer take as many steps!" << std::endl;
}

/********************************************************************* 
** Description: void warpEncounter()
*               
*********************************************************************/
void warpEncounter()
{
    std::cout << "A small sign at your feet says:" << std::endl;
    std::cout << "  'How'd you like to go somewhere random?'" << std::endl;
    std::cout << "   Please enter your choice below:" << std::endl;
    std::cout << "        1. Take a chance! You could save yourself some much needed energy! What could possibly go wrong?" << std::endl;
    std::cout << "          2. Leave it alone" << std::endl;
    std::cout << "   --> ";
}

/********************************************************************* 
** Description: void monsterEncounter()
*               
*********************************************************************/
void monsterEncounter()
{
    std::cout << "   The monster is too close! It lashes out and the fight begins!" << std::endl;
    std::cout << "     The beast roars: ROCK, PAPER, SCISSORS" << std::endl;
    std::cout << "       You react with:" << std::endl;
    std::cout << "         1. Rock" << std::endl;
    std::cout << "           2. Paper" << std::endl;
    std::cout << "             3. Scissors" << std::endl;
    std::cout << "               4. A compliment" << std::endl;
    std::cout << "     --> ";
}

/********************************************************************* 
** Description: void keyEncounterMonster()
*               
*********************************************************************/
void keyEncounterMonster()
{
    std::cout << "The monster is vanquisehd. All that's left of its massive frame is a key. Conservation of energy be damned." << std::endl;
    std::cout << "   Please enter your choice below:" << std::endl;
    std::cout << "        1. Pick up the key" << std::endl;
    std::cout << "          2. Leave it alone" << std::endl;
    std::cout << "   --> ";    
}

/********************************************************************* 
** Description: void keyHoleEncounter()
*               
*********************************************************************/
void keyHoleEncounter()
{
    std::cout << "With two keys in hand, a new door has appeared in the room's center. An exit to the outside perhaps?" << std::endl;
    std::cout << "   Please enter your choice below:" << std::endl;
    std::cout << "        1. Leave this place" << std::endl;
    std::cout << "          2. Continue on" << std::endl;
    std::cout << "   --> ";    
}
