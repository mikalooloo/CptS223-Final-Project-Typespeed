/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* header.h
*/
#ifndef HEADER_H
#define HEADER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <array>

class Button; // forward declaration
class Settings;
template<typename K, typename V>class HashTable;

enum Action // used to tell what the button is supposed to do when clicked
{
    NONE,
    // MAIN MENU ACTIONS
    PLAY,
    RULES,
    OPTIONS,
    EXIT,
    // OPTIONS ACTIONS
    DIFF,
    DIR,
    MUS,
    EFF,
    BACK
};

enum Direction // used during gameplay to help move things like the background and text
{
    RIGHT,
    LEFT,
    UP,
    DOWN,
    ALL
};

enum Difficulty
{
    EASY,
    NORMAL,
    HARD
};

/* 
*  Function: createText
*  Description: loads the filePath into l and runs an error if it doesn't open
*  Inputs: T * l, string filePath (path to asset (font/texture/etc))
*  Outputs: T is a pointer
*  Preconditions: n/a
*  Date Created: 12/04/2020
*  Date Last Modified: 12/06/2020
*  Update Notes: changed function name from createText to createAsset to be more accurate
*/
template <class T>
void createAsset(T * l, std::string filePath)
{
    if (!l->loadFromFile(filePath))
    {
        throw std::runtime_error("Asset failed to load");
    }
}

/* 
*  Function: gamePlay
*  Description: plays the game until the player loses or force quits
*  Inputs: RenderWindow window, Font screenFont
*  Outputs: n/a
*  Preconditions: play was selected
*  Date Created: 12/06/2020
*  Date Last Modified: 12/09/2020
*  Update Notes: added word functionality
*  12/08/2020 - added Settings in parameter list
*  12/07/2020 - added hash table
*/
void gamePlay(sf::RenderWindow &window, sf::Font &screenFont, Settings &settings);

/* 
*  Function: addNewWord
*  Description: uses the hash's findRandomWord function then calls randomPlacement(), to generate a new random word and its random placement
*  Inputs: HashTable * hash, vector<Text, Direction> wordVector, Direction d
*  Outputs: n/a
*  Preconditions: a new word needs to be added onscreen
*  Date Created: 12/09/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void addNewWord(HashTable<std::string, int> *hash, std::vector<std::pair<sf::Text, Direction>> &wordVector, Direction d);
/* 
*  Function: randomPlacement
*  Description: picks a random placement to go in the Direction d, adds it to the wordVector and ensures it's not going to overlap another word
*  Inputs: string randomWord, vector<Text, Direction> wordVector, Direction d
*  Outputs: n/a
*  Preconditions: a new word is being added (addNewWord)
*  Date Created: 12/09/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void randomPlacement(std::string randomWord, std::vector<std::pair<sf::Text, Direction>> &wordVector, Direction d);
/* 
*  Function: updateWords
*  Description: updates the position of each word dependent on the direction they're going (moves it at speed speed)
*  Inputs: vector<Text, Direction> wordVector, double speed
*  Outputs: n/a
*  Preconditions: n/a
*  Date Created: 12/09/2020
*  Date Last Modified: 12/10/2020
*  Update Notes: changed speed from an int to double
*/
void updateWords(std::vector<std::pair<sf::Text, Direction>> &wordVector, double speed);
/* 
*  Function: updateComboCPS
*  Description: updates the combo and CPS numbers based on whether or not the player entered a correct word (bool correct)
*  Inputs: bool correct, int combo, Text comboNum, int correctCharacters, double cps, string cpsString, Text cpsNum, Clock clock, string playerKey
*  Outputs: n/a
*  Preconditions: something was entered
*  Date Created: 12/06/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void updateComboCPS(bool correct, int &combo, sf::Text &comboNum, int &correctCharacters, double &cps, std::string &cpsString, sf::Text &cpsNum, sf::Clock &clock, std::string &playerKey);

/* 
*  Function: loadMainMenu
*  Description: clears the window, draws background, all buttons and text, displays window for main menu
*  Inputs: RenderWindow * window, Sprite * background, button and text arrays
*  Outputs: n/a
*  Preconditions: the screen is on the main menu
*  Date Created: 12/05/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void loadMainMenu(sf::RenderWindow * window, sf::Sprite * background, std::array<Button *, 4> &buttonArray, std::array<sf::Text *, 6> &textArray);

/* 
*  Function: loadGamePlay
*  Description: clears the window, draws background, text, displays window for game
*  Inputs: RenderWindow * window, Sprite * background, text array
*  Outputs: n/a
*  Preconditions: gamePlay is running
*  Date Created: 12/06/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void loadGamePlay(sf::RenderWindow * window, sf::Sprite * background, std::array<sf::Text *, 5> &textArray, std::vector<std::pair<sf::Text, Direction>> &wordVector);

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