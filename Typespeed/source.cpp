/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* source.cpp
*/
#include "header.h"
#include "Button.hpp"
#include "MovingBackground.hpp"
#include "Settings.hpp"
#include "hash.h"

#include <cmath> // for floor, for calculating cps

#define BACKSPACE 8
#define ENTER 13
#define SPACE 32

void gamePlay(sf::RenderWindow &window, sf::Font &screenFont, Settings &settings)
{
    // *******BACKGROUND*******
    MovingBackground background("Images/BlackBackground.jpg",settings.getDirection());

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

    int limit;
    if (settings.getDifficulty() == EASY) limit = 4;
    else if (settings.getDifficulty() == NORMAL) limit = 5;
    else limit = 6;

    std::vector<sf::Text> wordVector;

    for (int i = 0; i < limit; ++i)
    {
        sf::Text word("",wordFont,30);
        wordVector.push_back(word);
    }

    // *******VARIABLES*******
    sf::String playerInput; // used to read playerInput
    std::string playerKey = ""; // used to search hash table and helps keep track of # of correct characters

    std::string randomWord = "";

    int correctCharacters = 0; 
    double cps = 0.0;
    std::string cpsString = ""; // used to shorten string to one decimal place
    int combo = 0;

    sf::Clock clock;
    sf::Time time;
    int seconds; // every this many seconds, a new word appears on the screen
    if (settings.getDifficulty() == EASY) seconds = 3; // temporary, for testing
    else if (settings.getDifficulty() == NORMAL) seconds = 6;
    else seconds = 3;

    //********HASH TABLE*******
    std::ifstream infile;
    infile.open("Files/NormalWords.csv");
    HashTable<std::string, int> *hash = new HashTable<std::string, int>(53); // size 53 because word count is 23 * 2 = 52 and next prime is 53
    std::string word;
    while (getline(infile, word, ',')) hash->insert(std::make_pair(word,0));
    infile.close(); 

    time = clock.restart();
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

        if (clock.getElapsedTime().asSeconds() - time.asSeconds() > seconds) // if this is true, then we need to add a new word
        {
            randomWord = hash->findRandom(); // finds a random word - needs to check if its onscreen already or not
            randomPlacement(randomWord, wordVector, settings.getDirection()); // puts it in a random placement
            time = clock.restart();
        } 
        // search hash table for playerKey if playerKey is not "", add character # to correct cps if it was found and is on the screen, remove from onscreen
        // also add one to combo if it's correct, set to 0 if not

        if (playerKey != "") updateComboCPS(true,combo,comboNum,correctCharacters,cps,cpsString,cpsNum,clock,playerKey);
            
        background.update();

        loadGamePlay(&window, background.getSprite(), textArray, wordVector);
    }

    //for (int i = 0; i < wordVector.size(); ++i)
    //{
        //delete wordVector[i];
    //}
}

void randomPlacement(std::string randomWord, std::vector<sf::Text> &wordVector, Direction d)
{
    sf::Vector2f randomXY(0.f,0.f);
    long unsigned int i = 0;

    if (d == ALL) // if all directions, pick a random one
    {
        int random = rand() % 4;
        d = (Direction)random;
    }

    switch (d)
    {
        case RIGHT: // if going to the right (coming from the left)
            randomXY.x = -20.f;
            randomXY.y = rand() % 700 + 5;
            for (i = 0; wordVector.at(i).getString() != ""; ++i); // this finds the next empty wordVector slot
            wordVector.at(i).setString(randomWord);
            wordVector.at(i).setPosition(randomXY);
            break;
        case LEFT: // if going to the left (coming from the right)
            randomXY.x = 1840.f;
            randomXY.y = rand() % 700 + 5;
            for (i = 0; wordVector.at(i).getString() != ""; ++i);
            wordVector.at(i).setString(randomWord);
            wordVector.at(i).setPosition(randomXY);
            break;
        case UP: // if going up (coming from below)
            randomXY.x = rand() % 1840;
            randomXY.y = 870.f;
            for (i = 0; wordVector.at(i).getString() != ""; ++i);
            wordVector.at(i).setString(randomWord);
            wordVector.at(i).setPosition(randomXY);
            break;
        case DOWN: // if going down (coming from above)
            randomXY.x = rand() % 1080 + 5;
            randomXY.y = -20.f;
            for (i = 0; wordVector.at(i).getString() != ""; ++i);
            wordVector.at(i).setString(randomWord);
            wordVector.at(i).setPosition(randomXY);
            break;
        default:
            break;
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

void loadMainMenu(sf::RenderWindow * window, sf::Sprite * background, std::array<Button *, 4> &buttonArray, std::array<sf::Text *, 6> &textArray)
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

void loadGamePlay(sf::RenderWindow * window, sf::Sprite * background, std::array<sf::Text *, 5> &textArray, std::vector<sf::Text> &wordVector)
{
    window->clear();
    window->draw(*background);
    for (long unsigned int i = 0; i < textArray.size(); ++i) // prints all text
    {
        window->draw(*textArray[i]);
    }

    for (long unsigned int i = 0; i < wordVector.size(); ++i)
    {
        if (wordVector.at(i).getString() != "") window->draw(wordVector[i]);
    }

    window->display();
}