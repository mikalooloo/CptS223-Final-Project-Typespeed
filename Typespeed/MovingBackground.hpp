/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* MovingBackground.hpp
*/
#ifndef MOVINGBACKGROUND_HPP
#define MOVINGBACKGROUND_HPP

#include "header.h"

class MovingBackground
{
private:
    sf::Texture texture;
    sf::Sprite background;

    Direction direction;
    double backgroundX;
    double backgroundY;

public:
    // ****************************CONSTRUCTORS****************************
    /* 
    *  Function: MovingBackground default constructor
    *  Description: created so this class can be used in another class
    *  Inputs: n/a
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    MovingBackground();
    /* 
    *  Function: MovingBackground explicit constructor
    *  Description: sets texture and sprite to texturePath, direction to d, and the other variables to 0
    *  Inputs: string texturePath, Direction D
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    MovingBackground(std::string texturePath, Direction d);

    // ****************************SETTERS****************************
    /* 
    *  Function: setTexture
    *  Description: sets the texture t to the sprite
    *  Inputs: string t (texturePath)
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setTexture(std::string t);
    /* 
    *  Function: setDirection
    *  Description: sets direction to d
    *  Inputs: Direction to d
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setDirection(Direction d);
    /* 
    *  Function: setX
    *  Description: sets backgroundX to x
    *  Inputs: double x
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setX(double x);
    /* 
    *  Function: setY
    *  Description: sets backgroundY to y
    *  Inputs: double y
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setY(double y);

    // ****************************GETTERS****************************
    /* 
    *  Function: getSprite
    *  Description: returns a pointer to the sprite
    *  Inputs: n/a
    *  Outputs: Sprite * background
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    sf::Sprite * getSprite(void);
    /* 
    *  Function: getDirection
    *  Description: return Direction 
    *  Inputs: n/a
    *  Outputs: Direction direction
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    Direction getDirection(void);
    /* 
    *  Function: getX
    *  Description: returns backgroundX
    *  Inputs: n/a
    *  Outputs: double backgroundX
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    double getX(void);
    /* 
    *  Function: getY
    *  Description: returns backgroundY
    *  Inputs: n/a
    *  Outputs: double backgroundY
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    double getY(void);

    // ****************************FUNCTIONS****************************
    /* 
    *  Function: update
    *  Description: moves the background at a constant rate in the specified direction
    *  Inputs: n/a
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/06/2020
    *  Date Last Modified: 12/08/2020
    *  Update Notes: added case ALL
    */
    void update(void);
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