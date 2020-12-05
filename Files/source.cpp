/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Meeonka (?)
* 12/11/2020
* source.cpp
*/
#include "header.h"


void createText(sf::Font * f, std::string fString)
{
    if (!f->loadFromFile(fString))
    {
        throw std::runtime_error("Font failed to load");
    }
}