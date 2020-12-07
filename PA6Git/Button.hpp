/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* Button.hpp
*/
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "header.h"

enum ClickState
{
    NORMAL,
    CLICKED,
    HOVERING
};

class Button
{
private:

    sf::Texture normalTexture; 
    sf::Texture hoveringTexture;

    sf::Sprite normal;
    sf::Sprite hovering;
    sf::Sprite * spriteState;

    MenuAction buttonPurpose;
    ClickState clickState;

    sf::Vector2f location;

public:
    // ****************************CONSTRUCTORS****************************
    /* 
    *  Function: Button explicit constructor
    *  Description: uses setTexture with normalT and hoveringT to set normalTexture/normal and hoveringTexture/hovering, uses l to set location, and uses p to set buttonPurpose. Also sets spriteState to normal and clickState to normal
    *  Inputs: string normalT and string hoveringT, which should both be paths to the images to use, MenuAction p which should be the action you want the button take when clicked, and Vector2f the location where you want the button to be
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/02/2020
    *  Date Last Modified: 12/04/2020
    *  Update Notes: changed clickState from bool to ClickState
    */
    Button(std::string normalT, std::string hoveringT, MenuAction p, sf::Vector2f l);


    // ****************************SETTERS****************************
    /* 
    *  Function: setTexture
    *  Description: if bool is true, loads the string for normalTexture and loads the normal sprite, otherwise if bool is false does the same for hovering
    *  Inputs: string t, which should be the path to the image, and bool normal (true if setting the normalTexture and sprite, false if setting the hoveringTexture and sprite)
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/02/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setTexture(std::string t, bool normal);
    /* 
    *  Function: setClickState
    *  Description: sets clickState as c and updates the spriteState appropiately
    *  Inputs: ClickState c
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/02/2020
    *  Date Last Modified: 12/05/2020
    *  Update Notes: changed the function name from setState to setClickState to match other functions
    *  12/4/2020 - changed input parameter from bool to ClickState
    */
    void setClickState(ClickState c);
    /* 
    *  Function: setLocation
    *  Description: sets the location of the button to l
    *  Inputs: Vector2f l
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/04/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setLocation(sf::Vector2f l);
    /* 
    *  Function: setPurpose
    *  Description: sets the buttonPurpose to p
    *  Inputs: MenuAction p
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/04/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setPurpose(MenuAction p);

    // ****************************GETTERS****************************
    /* 
    *  Function: getPurpose
    *  Description: returns the button's purpose via MenuAction 
    *  Inputs: n/a
    *  Outputs: MenuAction
    *  Preconditions: n/a
    *  Date Created: 12/04/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    MenuAction getPurpose(void);
    /* 
    *  Function: getClickState
    *  Description: returns ClickState of button
    *  Inputs: n/a
    *  Outputs: ClickState
    *  Preconditions: n/a
    *  Date Created: 12/02/2020
    *  Date Last Modified: 12/04/2020
    *  Update Notes: changed return type from bool to ClickState
    */
    ClickState getClickState(void);
    /* 
    *  Function: getSprite
    *  Description: returns sf::Sprite of the current Sprite (spriteState)
    *  Inputs: n/a
    *  Outputs: sf::Sprite
    *  Preconditions: n/a
    *  Date Created: 12/02/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    sf::Sprite getSprite(void);

    // ****************************FUNCTIONS****************************
    /* 
    *  Function: checkClick
    *  Description: checks if the mouse is inside the sprite and if clicked is false changes the texture to hovering and clickState to hovering, if clicked is true it returns the button's purpose, but if the mouse is not inside the spite, changes the texture to normal and clickState to normal
    *  Inputs: Vector2f mousePos (will need to translate mouse coordinates from 2i to 2f), bool clicked 
    *  Outputs: MenuAction 
    *  Preconditions: n/a
    *  Date Created: 12/02/2020
    *  Date Last Modified: 12/04/2020
    *  Update Notes: changed the return type from void to MenuAction, so buttons can do something now, and added bool clicked to add hovering function of button
    */
    MenuAction checkClick(sf::Vector2f mousePos, bool clicked);
};

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