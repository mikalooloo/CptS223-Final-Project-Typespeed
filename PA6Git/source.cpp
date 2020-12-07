/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* source.cpp
*/
#include "header.h"
#include "Button.hpp"
#include "MovingBackground.hpp"

#include <cmath> // for floor, for calculating cps

#define BACKSPACE 8
#define ENTER 13
#define SPACE 32

void gamePlay(sf::RenderWindow &window, sf::Font &screenFont)
{
    // *******BACKGROUND*******
    MovingBackground background("Images/BlackBackground.jpg",RIGHT);

    // *******FONTS AND TEXT*******
    sf::Font playerFont;
    createAsset<sf::Font>(&playerFont, "Fonts/BetsyFlanagan.ttf");
    sf::Font wordFont;
    createAsset<sf::Font>(&wordFont,"Fonts/Typewriter.ttf");

    sf::Text playerText("", playerFont, 70);
    playerText.setPosition(150.f, 700.f);

    sf::Text cpsText("CPS", screenFont, 30);
    cpsText.setPosition(1500.f,700.f);
    sf::Text cpsNum("0.0", wordFont, 30);
    cpsNum.setPosition(1510.f, 740.f);

    sf::Text comboText("Combo", screenFont, 30);
    comboText.setPosition(1600.f,700.f);
    sf::Text comboNum("0", wordFont, 35);
    comboNum.setPosition(1649.f, 740.f);

    std::array<sf::Text *, 5> textArray = { &playerText, &cpsText, &cpsNum, &comboText, &comboNum };

    // *******VARIABLES*******
    sf::String playerInput; // used to read playerInput
    std::string playerKey = ""; // used to search hash table and helps keep track of # of correct characters

    int correctCharacters = 0; 
    double cps = 0.0;
    std::string cpsString = ""; // used to shorten string to one decimal place
    int combo = 0;

    sf::Clock clock;

    // *******GAMEPLAY*******
    while (window.isOpen())
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::TextEntered) // if player is typing
            {
                switch (event.text.unicode)
                {
                    case BACKSPACE: // if backspace, delete the last character
                        if(playerInput.getSize() != 0) playerInput.erase(playerInput.getSize() -1, 1);
                        break;
                    case ENTER: // if enter, save the string to check validity and clear the screen
                        playerKey = playerInput;
                        playerInput.clear();
                        break;
                    default: // if neither of those, it's a character, so display it on the screen (up to 15 characters limit)
                        if(playerInput.getSize() < 15 && event.text.unicode != SPACE) playerInput += event.text.unicode;
                        break;
                }

                playerText.setString(playerInput);
            }

        }


        // search hash table for playerKey if playerKey is not "", add character # to correct cps if it was found and is on the screen
        // also add one to combo if it's correct, set to 0 if not

        if (playerKey != "") updateComboCPS(true,combo,comboNum,correctCharacters,cps,cpsString,cpsNum,clock,playerKey);
            
        background.update();

        loadGamePlay(&window, background.getSprite(), textArray);
    }
}

void updateComboCPS(bool correct, int &combo, sf::Text &comboNum, int &correctCharacters, double &cps, std::string &cpsString, sf::Text &cpsNum, sf::Clock &clock, std::string &playerKey)
{
    if (correct) // if the word entered was correct,
    {
        ++combo; // add one to their current combo
        comboNum.setString(std::to_string(combo));

        correctCharacters += playerKey.size(); // and add to their CPS
        cps = (double)correctCharacters/clock.getElapsedTime().asSeconds(); // gets correct characters per sec
        cpsString = std::to_string(cps);
        // this next line is assuming no one has over 9.99 correct characters per second cause that feels impossible
        cpsString.erase(cpsString.begin()+3,cpsString.end()); // cuts off everything after the first decimal place
        cpsNum.setString(cpsString);
    }
    else // if it wasn't correct,
    {
        combo = 0; // reset their combo
        comboNum.setString(std::to_string(combo));
    }

    playerKey = "";
}

void loadMainMenu(sf::RenderWindow * window, sf::Sprite * background, std::array<Button *, 4> buttonArray, std::array<sf::Text *, 6> textArray)
{
    window->clear();

    window->draw(*background);
    
    for (long unsigned int i = 0; i < buttonArray.size(); ++i) // prints all buttons
    {
        window->draw(buttonArray[i]->getSprite());
    }

    for (long unsigned int i = 0; i < textArray.size(); ++i) // prints all text
    {
        window->draw(*textArray[i]);
    }

    window->display();
}

void loadGamePlay(sf::RenderWindow * window, sf::Sprite * background, std::array<sf::Text *, 5> textArray)
{
    window->clear();
    window->draw(*background);
    for (long unsigned int i = 0; i < textArray.size(); ++i) // prints all text
    {
        window->draw(*textArray[i]);
    }
    window->display();
}