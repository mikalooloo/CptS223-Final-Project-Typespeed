/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* Settings.cpp
*/
#include "Settings.hpp"
#include "MovingBackground.hpp"
#include "Button.hpp"

// ****************************CONSTRUCTORS****************************
    Settings::Settings(std::array<Button *, 13> * b, std::array<sf::Text *, 7> * t)
    {
        difficulty = EASY; // default difficulty is easy
        direction = RIGHT; // default direction is right
        last = RIGHT;
        music = true;      // default music and sound effects are on
        soundEffects = true;

        background.setTexture("Images/BlackBackground.jpg");

        buttonArray = *b;
        textArray = *t;

        wait = false;
    }

    // ****************************SETTERS****************************
    void Settings::setDifficulty(Difficulty d)
    {
        difficulty = d;
    }
    void Settings::setDirection(Direction t)
    {
        direction = t;
    }
    void Settings::setMusic(bool m)
    {
        music = m;
    }
    void Settings::setSoundEffects(bool s)
    {
        soundEffects = s;
    }
    void Settings::setButtonArray(std::array<Button *, 13> * b)
    {
        buttonArray = *b;
    }
    void Settings::setTextArray(std::array<sf::Text *, 7> * t)
    {
        textArray = *t;
    }

    // ****************************GETTERS****************************
    Difficulty Settings::getDifficulty(void)
    {
        return difficulty;
    }
    Direction Settings::getDirection(void)
    {
        return direction;
    }
    bool Settings::getMusic(void)
    {
        return music;
    }
    bool Settings::getSoundEffects(void)
    {
        return soundEffects;
    }
    std::array<Button *, 13> * Settings::getButtonArray(void)
    {
        return &buttonArray;
    }
    std::array<sf::Text *, 7> * Settings::getTextArray(void)
    {
        return &textArray;
    }

    // ****************************FUNCTIONS****************************
    Action Settings::checkButtons(bool clicked, sf::Vector2f mousePos)
    {
        Action result = NONE;

        if (clicked) // if the mouse was clicked
        {
            for (long unsigned int i = 0; i < buttonArray.size() && result == NONE; ++i) // check if any of the buttons got clicked
            {
                result = buttonArray[i]->checkClick(mousePos, true);
            }
        }
        else // if the mouse wasn't clicked
        {
            for (long unsigned int i = 0; i < buttonArray.size(); ++i) // check if the mouse is hovering over any of the buttons
            {
                buttonArray[i]->checkClick(mousePos, false);
            }
        }

        // if result is none, then a button wasn't pressed, so change result back to OPTIONS because otherwise it'll take us out of the OPTIONS screen (switch case in main)
        // if wait is true and the player isn't trying to go back to the main menu, also change the result to OPTIONS because wait means a button was pressed lately so let's give it a cooldown!
        if (result == NONE || (wait && result != BACK)) result = OPTIONS;
        else if (result == BACK) result = NONE; // if result is to go back, change it to NONE or aka main menu

        // do not allow to change the direction if the difficulty is hard
        if (difficulty == HARD && result == DIR) result = OPTIONS;
        
        // if a button has been pressed, we need to give it a cooldown before it can be pressed again
        checkTime(result); // this checks to see if we need to add or remove a button cooldown

        return result;
    }
    void Settings::checkTime(Action result)
    {
        if (!wait && result != NONE) // if result isn't none, then that means a button has been pressed. if wait is false then there is no current cooldown
        {
            timer.restart();
            wait = true; // so make a cooldown
        }
        
        // after some milliseconds, remove the cooldown
        if (wait) if (timer.getElapsedTime().asMilliseconds() > 100) wait = false;
        
    }
    void Settings::displayOptions(sf::RenderWindow * window)
    {
        window->clear();

        window->draw(*background.getSprite());

        // drawing the difficulty button
        if (difficulty == EASY) window->draw(buttonArray[0]->getSprite());
        else if (difficulty == NORMAL) window->draw(buttonArray[1]->getSprite());
        else window->draw(buttonArray[2]->getSprite());

        // drawing the direction button
        if (direction == RIGHT) window->draw(buttonArray[3]->getSprite());
        else if (direction == LEFT) window->draw(buttonArray[4]->getSprite());
        else if (direction == UP) window->draw(buttonArray[5]->getSprite());
        else if (direction == DOWN) window->draw(buttonArray[6]->getSprite());
        else window->draw(buttonArray[7]->getSprite());

        // drawing the music button
        if (music) window->draw(buttonArray[8]->getSprite());
        else window->draw(buttonArray[9]->getSprite());

        // drawing the sound effects button
        if (soundEffects) window->draw(buttonArray[10]->getSprite());
        else window->draw(buttonArray[11]->getSprite());

        // drawing the back button
        window->draw(buttonArray[12]->getSprite());

        for (long unsigned int i = 0; i < textArray.size(); ++i) // prints all text
        {
            window->draw(*textArray[i]);
        }

        window->display();
    }
    Action Settings::nextButton(Action a)
    {
        switch (a) // depending on the button pressed
        {
            case DIFF: // if the difficulty button was pressed, change it to the next difficulty
                if (difficulty == EASY) // if it was easy, go to normal
                {
                    difficulty = NORMAL;
                }
                else if (difficulty == NORMAL) // if it was on normal, go to hard
                {
                    difficulty = HARD;
                    last = direction;
                    direction = ALL; // and change the direction to ALL for hard mode
                    background.setDirection(direction);
                }
                else // if it was hard, go to easy
                {
                    difficulty = EASY; 
                    direction = last; // and turn it back to whatever direction it was before it was ALL
                    background.setDirection(direction);
                }
                
                a = OPTIONS; // this prevents from looping (if it stayed as DIF it would loop in here a bunch) and OPTIONS makes it so we stay on the OPTIONS screen
                break;
            case DIR: // if the direction button was pressed, change it to the next direction
                if (direction == RIGHT) direction = LEFT;
                else if (direction == LEFT) direction = UP;
                else if (direction == UP) direction = DOWN;
                else direction = RIGHT;

                background.setDirection(direction); // change the moving background to match this!
                a = OPTIONS;
                break;
            case MUS: // if the music button was pressed, toggle 
                if (music) music = false;
                else music = true;

                a = OPTIONS;
                break;
            case EFF: // if the sound effects button was pressed, toggle
                if (soundEffects) soundEffects = false;
                else soundEffects = true;

                a = OPTIONS;
                break;
            case BACK: // if back, change the action to NONE so main will return us to the main menu
                a = NONE;
                break;
            default:
                break;
        }

        background.update(); // update the location of the background

        return a;
    }