#include "Button.hpp"

Button::Button(std::string normalT, std::string clickedT, sf::Vector2f l)
{
    setTexture(normalT, true);
    setTexture(clickedT,false);
    this->spriteState = &this->normal;

    this->location = l;
    this->normal.setPosition(location);
    this->clicked.setPosition(location);

    clickState = false;
}

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
    else // if false, then load the t texture for clicked
    {
        if(!clickedTexture.loadFromFile(t))
        {
            throw std::runtime_error("Texture failed to load");
        }
        this->clicked.setTexture(clickedTexture);
    }
}

// Setters
void Button::setState(bool c) 
{
    clickState = c;
    if (clickState) spriteState = &clicked; // if clickState is true, change sprite to clicked as well
    else spriteState = &normal; // otherwise it's no longer clicked, change sprite back to normal
}

// Getters
bool Button::getClickState(void) 
{
    return clickState;
}
sf::Sprite Button::getSprite(void) 
{
    return *spriteState;
}

// Functions
void Button::checkClick(sf::Vector2f mousePos) 
{
    // if the mouse position is inside the sprite, set the clickState to true! otherwise set it to false
    if (spriteState->getGlobalBounds().contains(mousePos)) setState(true); 
    else setState(false);
}