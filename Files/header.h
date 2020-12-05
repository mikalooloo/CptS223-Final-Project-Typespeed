/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Meeonka (?)
* 12/11/2020
* header.h
*/
#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include <iostream>

enum MenuAction 
{
    PLAY,
    RULES,
    OPTIONS,
    EXIT,
    NONE
};

void createText(sf::Font * f, std::string fString);

#endif