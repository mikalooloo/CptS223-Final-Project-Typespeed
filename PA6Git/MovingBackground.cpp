/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* MovingBackground.cpp
*/
#include "MovingBackground.hpp"

// ****************************CONSTRUCTORS****************************
MovingBackground::MovingBackground(std::string texturePath, Direction d)
{
    setTexture(texturePath);

    direction = d;
    backgroundX = 0;
    backgroundY = 0;

    update();
}

// ****************************SETTERS****************************
void MovingBackground::setTexture(std::string t)
{
    createAsset<sf::Texture>(&texture,t);
    texture.setSmooth(false); texture.setRepeated(true);
    this->background.setTexture(texture);
}
void MovingBackground::setDirection(Direction d)
{
    direction = d;
}
void MovingBackground::setX(double x)
{
    backgroundX = x;
}
void MovingBackground::setY(double y)
{
    backgroundY = y;
}

// ****************************GETTERS****************************
sf::Sprite * MovingBackground::getSprite(void)
{
    return &background;
}
Direction MovingBackground::getDirection(void)
{
    return direction;
}
double MovingBackground::getX(void)
{
    return backgroundX;
}
double MovingBackground::getY(void)
{
    return backgroundY;
}

// ****************************FUNCTIONS****************************
void MovingBackground::update(void)
{
    switch (direction)
    {
        case RIGHT: // makes the background look like it's moving to the right,
            if (backgroundX < 1920) backgroundX -= 0.1;
            else backgroundX = 0;

            background.setTextureRect(sf::IntRect(backgroundX,0,1920,1080));
            break;

        case LEFT: // to the left,
            if (backgroundX > 0) backgroundX += 0.1;
            else backgroundX = 1920;

            background.setTextureRect(sf::IntRect(backgroundX,0,1920,1080));
            break;

        case UP: // up,
            if (backgroundY > 0) backgroundY += 0.1;
            else backgroundY = 1080;

            background.setTextureRect(sf::IntRect(0,backgroundY,1920,1080));
            break;

        case DOWN: // or down
            if (backgroundY < 1080) backgroundY -= 0.1;
            else backgroundY = 0;

            background.setTextureRect(sf::IntRect(0,backgroundY,1920,1080));
            break;
    }
}