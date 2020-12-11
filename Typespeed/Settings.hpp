/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* Settings.hpp
*/

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "header.h"
#include "MovingBackground.hpp"

class Button;

class Settings
{
private:
    Difficulty difficulty;
    Direction direction;
    Direction last;

    bool music;
    bool soundEffects;

    MovingBackground background;

    std::array<Button *, 13> buttonArray;
    std::array<sf::Text *, 7> textArray;

    sf::Clock timer;
    bool wait;

public:
    // ****************************CONSTRUCTORS****************************
    /* 
    *  Function: Settings explicit constructor
    *  Description: sets difficulty to easy, direction to right, music and soundEffects to true and wait to false, sets background, and sets the text and buttonArrays to t and b respectively
    *  Inputs: Button * barray[13] and Text * tarray[7]
    *  Outputs: n/a
    *  Preconditions: the inputs are already filled with buttons/texts respectively
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    Settings(std::array<Button *, 13> * b, std::array<sf::Text *, 7> * t);

    // ****************************SETTERS****************************
    /* 
    *  Function: setDifficulty
    *  Description: sets difficulty to d
    *  Inputs: Difficulty d
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setDifficulty(Difficulty d);
    /* 
    *  Function: setDirection
    *  Description: sets direction to t
    *  Inputs: Direction t
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setDirection(Direction t);
    /* 
    *  Function: setMusic
    *  Description: sets bool music to m
    *  Inputs: bool m
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setMusic(bool m);
    /* 
    *  Function: setSoundEffects
    *  Description: set bool soundEffects to s
    *  Inputs: bool s
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setSoundEffects(bool s);
    /* 
    *  Function: setButtonArray
    *  Description: sets buttonArray to b
    *  Inputs: Button * array[13]
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setButtonArray(std::array<Button *, 13> * b);
    /* 
    *  Function: setTextArray
    *  Description: sets textArray to t
    *  Inputs: Text * array[7]
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void setTextArray(std::array<sf::Text *, 7> * t);

    // ****************************GETTERS****************************
    /* 
    *  Function: getDifficulty
    *  Description: returns difficulty
    *  Inputs: n/a
    *  Outputs: Difficulty difficulty
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    Difficulty getDifficulty(void);
    /* 
    *  Function: getDirection
    *  Description: returns direction
    *  Inputs: n/a
    *  Outputs: Direction direction
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    Direction getDirection(void);
    /* 
    *  Function: getMusic
    *  Description: returns music (true/false)
    *  Inputs: n/a
    *  Outputs: bool music
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    bool getMusic(void);
    /* 
    *  Function: getSoundEffects
    *  Description: returns soundEffects (true/false)
    *  Inputs: n/a
    *  Outputs: bool soundEffects
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    bool getSoundEffects(void);
    /* 
    *  Function: getButtonArray
    *  Description: returns a pointer to buttonArray
    *  Inputs: n/a
    *  Outputs: Button * * array[13]
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    std::array<Button *, 13> * getButtonArray(void);
    /* 
    *  Function: getTextArray
    *  Description: returns a pointer to textArray
    *  Inputs: n/a
    *  Outputs: Text * * array[7]
    *  Preconditions: n/a
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    std::array<sf::Text *, 7> * getTextArray(void);

    // ****************************FUNCTIONS****************************
    /* 
    *  Function: checkButtons
    *  Description: checks to see if any buttons were clicked and returns OPTIONS if none were picked, NONE if back was picked, or other depending on the button
    *  Inputs: bool clicked, sf::Vector2f mousePos
    *  Outputs: Action (no buttons: OPTIONS, back: NONE, other: other)
    *  Preconditions: result is OPTIONS/currently on the OPTIONS screen
    *  Date Created: 12/08/2020
    *  Date Last Modified: 12/10/2020
    *  Update Notes: rearranged the parameters to match the Button class's checkClick
    */
    Action checkButtons(sf::Vector2f mousePos, bool clicked);
    /* 
    *  Function: checkTime
    *  Description: checks to see if we should add or remove a button click cooldown
    *  Inputs: Action result
    *  Outputs: n/a
    *  Preconditions: checkButtons() has been called aka we are on the OPTIONS screen
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void checkTime(Action result);
    /* 
    *  Function: displayOptions
    *  Description: displays the OPTIONS screen
    *  Inputs: RenderWindow * window
    *  Outputs: n/a
    *  Preconditions: we are on the OPTIONS screen
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void displayOptions(sf::RenderWindow * window);
    /* 
    *  Function: displayPause
    *  Description: displays the PAUSE screen
    *  Inputs: RenderWindow * window
    *  Outputs: n/a
    *  Preconditions: n/a
    *  Date Created: 
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    void displayPause(sf::RenderWindow * window);
    /* 
    *  Function: nextButton
    *  Description: if a button was clicked, it activates the button, also updates background
    *  Inputs: Action a
    *  Outputs: Action (OPTIONS, unless going back in which case it would return NONE)
    *  Preconditions: we are on the OPTIONS screen
    *  Date Created: 12/08/2020
    *  Date Last Modified: n/a
    *  Update Notes: n/a
    */
    Action nextButton(Action a);

};

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