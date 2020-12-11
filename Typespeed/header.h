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
    EXIT, // ALSO USED IN GAMEPLAY TO EXIT
    // OPTIONS ACTIONS
    DIFF,
    DIR,
    MUS,
    EFF,
    BACK // ALSO USED IN GAMEPLAY TO RETURN TO MAIN MENU
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
*  Update Notes: changed speed from an int to double, changed return type from void to int
*/
int updateWords(std::vector<std::pair<sf::Text, Direction>> &wordVector, double speed);
/* 
*  Function: updateLifeTracker
*  Description: for every life lost, it dulls one of the sprites in the lifeArray by replacing it with one in the deadArray
*  Inputs: Sprite * lifeArray[3], Sprite * deadArray[3], int liveslost (how many to dull)
*  Outputs: n/a
*  Preconditions: at least one life has been lost (but will run fine if liveslost is 0)
*  Date Created: 12/10/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void updateLifeTracker(std::array<sf::Sprite *, 3> &lifeArray, std::array<sf::Sprite *, 3> &deadArray, int liveslost);
/* 
*  Function: updateComboCPS
*  Description: updates the combo and CPS numbers based on whether or not the player entered a correct word (bool correct)
*  Inputs: bool correct, int combo, Text comboNum, int correctCharacters, double cps, string cpsString, Text cpsNum, Clock clock, string playerKey
*  Outputs: n/a
*  Preconditions: something was entered
*  Date Created: 12/06/2020
*  Date Last Modified: 12/10/2020
*  Update Notes: added highestcombo to parameter list
*/
void updateComboCPS(bool correct, int &combo, int &highestCombo, sf::Text &comboNum, int &correctCharacters, double &cps, std::string &cpsString, sf::Text &cpsNum, sf::Clock &clock, std::string &playerKey);
/* 
*  Function: increaseDifficulty
*  Description: increases the speed of the words by 0.01 for every word typed correctly
*  Inputs: double speed
*  Outputs: n/a
*  Preconditions: a word has been typed correctly
*  Date Created: 12/10/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void increaseDifficulty(double &speed);
/* 
*  Function: randomTaunt
*  Description: picks a random taunt for the game over screen
*  Inputs: Text taunt
*  Outputs: n/a
*  Preconditions: n/a
*  Date Created: 12/10/2020
*  Date Last Modified: n/a
*  Update Notes: n/a
*/
void randomTaunt(sf::Text &taunt);
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
*  Date Last Modified: 12/10/2020
*  Update Notes: added lifeArray to parameter list
*/
void loadGamePlay(sf::RenderWindow * window, sf::Sprite * background, std::array<sf::Text *, 5> &textArray, std::vector<std::pair<sf::Text, Direction>> &wordVector, std::array<sf::Sprite *, 3> &lifeArray);

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