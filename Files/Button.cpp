
/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* Button.cpp
*/
#include "Button.hpp"

// ****************************CONSTRUCTORS****************************
Button::Button(std::string normalT, std::string hoveringT, MenuAction p, sf::Vector2f l)
{
    setTexture(normalT, true);
    setTexture(hoveringT,false);
    this->spriteState = &this->normal;

    buttonPurpose = p;
    clickState = NORMAL;

    this->location = l;
    this->normal.setPosition(location);
    this->hovering.setPosition(location);
}

// ****************************SETTERS****************************
void Button::setTexture(std::string t, bool normal)
{
    if (normal) // if true, then load the t texture for normal
    {
        if(!normalTexture.loadFromFile(t))
        {
            throw std::runtime_error("Texture failed to load");
        }
        this->normal.setTexture(normalTexture);
    }
    else // if false, then load the t texture for hovering
    {
        if(!hoveringTexture.loadFromFile(t))
        {
            throw std::runtime_error("Texture failed to load");
        }
        this->hovering.setTexture(hoveringTexture);
    }
}
void Button::setPurpose(MenuAction p)
{
    buttonPurpose = p;
}
void Button::setClickState(ClickState c) 
{
    clickState = c;
    if (clickState == HOVERING) spriteState = &hovering; // changes sprite to match the ClickState
    else spriteState = &normal; // otherwise no longer hovering, change sprite back to normal
}
void Button::setLocation(sf::Vector2f l)
{
    location = l;
}

// ****************************GETTERS****************************
MenuAction Button::getPurpose(void)
{
    return buttonPurpose;
}
ClickState Button::getClickState(void) 
{
    return clickState;
}
sf::Sprite Button::getSprite(void) 
{
    return *spriteState;
}

// ****************************FUNCTIONS****************************
MenuAction Button::checkClick(sf::Vector2f mousePos, bool clicked) 
{
    // if the mouse position is inside the sprite, 
    if (spriteState->getGlobalBounds().contains(mousePos)) 
    {
        if (!clicked) // and it hasn't been clicked
        {
            setClickState(HOVERING); // it must be hovering, return none but change the sprite to hovering
            return NONE;
        }
        else // if it has been clicked,
        {
            setClickState(CLICKED);
            return buttonPurpose; // return the button's purpose since it's been clicked
        }

    }
    else // if the mouse isn't inside the sprite,
    {
        setClickState(NORMAL); // return the button to normal and return none from this function
        return NONE;
    }
}