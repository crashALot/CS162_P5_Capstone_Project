/********************************************************************* 
** Author:      Glenn Kiefer
** Date:        08/15/18
** Description: 
*********************************************************************/
#include "menuValidate.hpp"
#include <iostream>

/********************************************************************* 
** Description: int mainMenuValidate()
*               Validates input from main menu function
*********************************************************************/
int mainMenuValidate()
{
    int go=1, length=0;
    std::string userIn;
    do
    {
        // http://www.cplusplus.com/forum/beginner/2624/
        // How to identify the Enter key when pressed alone 
        //std::getline(std::cin, userIn);
        std::cin >> userIn;
        length=userIn.length();
        if (userIn[0]==' ' || length>1 || (userIn[0]!='1' && userIn[0]!='2'))
        {
            std::cout << std::endl << "Please re-enter your choice as an integer 1 or 2: " << std::endl;
            std::cout << "   --> ";
        }
        else
        {
            // Work cited: https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
            go=0; // Signal variable exits while loop
            return((int)userIn[0]-'0'); // Converts char to int via ASCII code math
        }
    }
    while (go);
    return 0;
}

/********************************************************************* 
** Description: char playerActionValidate()
*               Validates input for e ach player action. Limits scope
*               of input to required characters
*********************************************************************/
char playerActionValidate()
{
    int go=1;
    char userIn;
    do
    {
        // http://www.cplusplus.com/forum/beginner/2624/
        // How to identify the Enter key when pressed alone 
        std::cin >> userIn;
        if (userIn==' ' || (userIn!='n' && userIn!='e' && userIn!='s' && userIn!='w' && userIn!='x' && userIn!='d' && userIn!='i' && userIn!='p'))
        {
            std::cout << std::endl << "Please re-enter your choice as a character as found in the instructions: " << std::endl;
            std::cout << "   Appropriate entries include: n, e, s, w, x, d, p, and i" << std::endl;
            std::cout  <<"      --> ";
        }
        else
        {
            go=0; // Signal variable exits while loop
            return(userIn); 
        }
    }
    while (go);
    return 0;
}
/********************************************************************* 
** Description: int inventoryDropValidate(int listLength)
*               Validates input for inventory selection. Since 
*               inventory can grow or shrink, an argument is needed
*               to know up to what item can be selected.
*********************************************************************/
int inventoryDropValidate(int listLength)
{
    int go=1, length=0;
    std::string userIn;
    do
    {
        std::cin >> userIn;
        length=userIn.length();
        if (userIn[0]==' ' || length>1 || (userIn[0]-'0')<1 || (userIn[0]-'0')>listLength)
        {
            std::cout << std::endl << "Please re-enter your choice as an integer between 1 and " << listLength <<": " << std::endl;
            std::cout << "   --> ";
        }
        else
        {
            // Work cited: https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
            go=0; // Signal variable exits while loop
            return((int)userIn[0]-'0'); // Converts char to int via ASCII code math
        }
    }
    while (go);
    return 0;
}