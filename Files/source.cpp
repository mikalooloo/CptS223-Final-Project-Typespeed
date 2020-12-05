/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* source.cpp
*/
#include "header.h"
#include "Button.hpp"

void createText(sf::Font * f, std::string fString)
{
    if (!f->loadFromFile(fString))
    {
        throw std::runtime_error("Font failed to load");
    }
}

void loadMainMenu(sf::RenderWindow * window, Button * playbutton, Button * rulesbutton, Button * optionsbutton, Button * exitbutton)
{
    window->clear();
    window->draw(playbutton->getSprite());
    window->draw(rulesbutton->getSprite());
    window->draw(optionsbutton->getSprite());
    window->draw(exitbutton->getSprite());
    window->display();
}