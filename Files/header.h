/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* header.h
*/
#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Button; // forward declaration

enum MenuAction 
{
    PLAY,
    RULES,
    OPTIONS,
    EXIT,
    NONE
};

/* 
*  Function: createText
*  Description: loads the fString path into f and runs an error if it doesn't open
*  Inputs: Font * f, string fString (path to font)
*  Outputs: f is a pointer
*  Preconditions: n/a
*  Date Created: 12/04/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void createText(sf::Font * f, std::string fString);

/* 
*  Function: loadMainMenu
*  Description: clears the window, draws all buttons, displays window for main menu
*  Inputs: RenderWindow window, then the four buttons for the main menu
*  Outputs: n/a
*  Preconditions: the screen is on the main menu
*  Date Created: 12/05/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void loadMainMenu(sf::RenderWindow * window, Button * playbutton, Button * rulesbutton, Button * optionsbutton, Button * exitbutton);

#endif


/* 
*  Function: 
*  Description:
*  Inputs:
*  Outputs:
*  Preconditions:
*  Date Created: 
*  Date Last Modified: 
*  Update Notes: 
*/