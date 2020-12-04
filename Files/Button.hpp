/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Meeonka
* 12/11/2020
* main.cpp
*/

#include <SFML/Graphics.hpp>
#include <iostream>

class Button
{
private:

    sf::Texture normalTexture; 
    sf::Texture clickedTexture;

    sf::Sprite normal;
    sf::Sprite clicked;
    sf::Sprite * spriteState;

    sf::Vector2f location;
    bool clickState;


public:
    // ****CONSTRUCTORS****
    /* 
    *  Function: Button explicit constructor
    *  Description: uses setTexture with normalT and clickedT to set normalTexture/normal and clickedTexture/clicked and uses l to set location. Also sets spriteState to normal and clickState to false
    *  Inputs: string normalT and string clickedT, which should both be paths to the images to use and Vector2f the location where you want the button to be
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/2/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    Button(std::string normalT, std::string clickedT, sf::Vector2f l);

    /* 
    *  Function: setTexture
    *  Description: if bool is true, loads the string for normalTexture and loads the normal sprite, otherwise if bool is false does the same for clicked
    *  Inputs: string t, which should be the path to the image, and bool normal (true if setting the normalTexture and sprite, false if setting the clickedTexture and sprite)
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/2/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setTexture(std::string t, bool normal);

    // ****SETTERS****
    /* 
    *  Function: setState
    *  Description: sets clickState as c and updates the spriteState (if clickState is true, updates to clicked, if false, updates to normal)
    *  Inputs: bool c (true if clicked)
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/2/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setState(bool c);

    // ****GETTERS****
    /* 
    *  Function: getClickState
    *  Description: returns bool of the clickState variable (true if currently clicked, false if not)
    *  Inputs: n/a
    *  Outputs: bool 
    *  Preconditions: n/a
    *  Date Created: 12/2/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    bool getClickState(void);
    /* 
    *  Function: getSprite
    *  Description: returns sf::Sprite of the current Sprite (spriteState)
    *  Inputs: n/a
    *  Outputs: sf::Sprite
    *  Preconditions: n/a
    *  Date Created: 12/2/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    sf::Sprite getSprite(void);

    // ****FUNCTIONS****
    /* 
    *  Function: checkClick
    *  Description: checks if the mouse is inside the sprite and if so, changes the texture to clicked and clickState to true, if not, changes the texture to normal and clickState to false
    *  Inputs: Vector2f mousePos (will need to translate mouse coordinates from 2i to 2f)
    *  Outputs: n/a
    *  Preconditions: mouse has been clicked
    *  Date Created: 12/2/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a 
    */
    void checkClick(sf::Vector2f mousePos);
};

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