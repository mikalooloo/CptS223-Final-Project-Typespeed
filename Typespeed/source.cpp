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

    std::vector<std::pair<sf::Text, Direction>> wordVector;

    for (int i = 0; i < 15; ++i) // makes 10 words so max 10 words on screen at a time
    {
        sf::Text word("",wordFont,30);
        wordVector.push_back(std::make_pair(word,RIGHT));
    }

    // *******VARIABLES*******
    sf::String playerInput; // used to read playerInput
    std::string playerKey = ""; // used to search hash table and helps keep track of # of correct characters

    std::string randomWord = "";

    int correctCharacters = 0; 
    double cps = 0.0; // correct characters per second
    std::string cpsString = ""; // used to shorten string to one decimal place
    int combo = 0;
    bool correct = false; // if what the player typed was correct or not

    sf::Clock clock;
    sf::Clock overallTime;
    int seconds; // every this many seconds, a new word appears on the screen
    double speed; // how fast the words go
    int onscreen = 0; // how many words are onscreen
    if (settings.getDifficulty() == EASY) 
    {
        seconds = 6; 
        speed = 0.5;
    }
    else if (settings.getDifficulty() == NORMAL) 
    {
        seconds = 4;
        speed = 1;
    }
    else 
    {
        seconds = 2;
        speed = 1.5;
    }


    //********HASH TABLE*******
    std::ifstream infile;
    infile.open("Files/NormalWords.csv");
    HashTable<std::string, int> *hash = new HashTable<std::string, int>(53); // size 53 because word count is 23 * 2 = 52 and next prime is 53
    std::string word;
    while (getline(infile, word, ',')) hash->insert(std::make_pair(word,1));
    infile.close(); 

    overallTime.restart();
    clock.restart();
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
                        for (long unsigned int i = 0; i < playerKey.length(); ++i) playerKey[i] = toupper(playerKey[i]);
                        playerInput.clear();
                        break;
                    default: // if neither of those, it's a character, so display it on the screen (up to 15 characters limit)
                        if(playerInput.getSize() < 15 && event.text.unicode != SPACE) playerInput += event.text.unicode;
                        break;
                }

                playerText.setString(playerInput);
            }

        }

        if (clock.getElapsedTime().asSeconds() > seconds && onscreen < 14) // if this is true, then we need to add a new word
        {
            ++onscreen;
            addNewWord(hash,wordVector,settings.getDirection());
            if (onscreen < 13 && (settings.getDifficulty() == HARD || (settings.getDifficulty() == NORMAL && combo > 10))) // if it's on hard or normal, add another word at the same time
            {
                addNewWord(hash,wordVector,settings.getDirection());
            }
            clock.restart();
        } 
        // search hash table for playerKey if playerKey is not "", add character # to correct cps if it was found and is on the screen, remove from onscreen
        // also add one to combo if it's correct, set to 0 if not

        if (playerKey != "") // if playerKey is not "", then player has entered something
        {
            if (hash->at(playerKey) == ONSCREEN) // if what the player entered is actually ONSCREEN
            {
                hash->setState(playerKey, VALID);
                --onscreen;
                correct = true;
                for (auto & v : wordVector)
                {
                    if (v.first.getString() == playerKey)
                    {
                        v.first.setString("");
                        break;
                    }
                }
            }
            else
            {
                correct = false;
            }
            
            updateComboCPS(correct,combo,comboNum,correctCharacters,cps,cpsString,cpsNum,overallTime,playerKey);
        }
            
        updateWords(wordVector, speed);
        background.update();

        loadGamePlay(&window, background.getSprite(), textArray, wordVector);
    }

}

void addNewWord(HashTable<std::string, int> *hash, std::vector<std::pair<sf::Text, Direction>> &wordVector, Direction d)
{
    std::string randomWord = hash->findRandom(); // finds a random word - needs to check if its onscreen already or not
    randomPlacement(randomWord, wordVector, d); // puts it in a random placement
}

void randomPlacement(std::string randomWord, std::vector<std::pair<sf::Text, Direction>> &wordVector, Direction d)
{
    sf::Vector2f randomXY(0.f,0.f);
    long unsigned int i = 0;
    bool overlapping = false;
    int count = 0;

    if (d == ALL) // if it can come from all directions,
    {
        int random = rand() % 4; // pick a direction randomly
        d = (Direction)random;      
    }

    do // do this while words are overlapping
    {  
        count = 0;
        switch (d) // generate a random placement
        {
            case RIGHT: // if going to the right (coming from the left)
                randomXY.x = -150.f;
                randomXY.y = rand() % 700 + 5;
                break;
            case LEFT: // if going to the left (coming from the right)
                randomXY.x = 1840.f;
                randomXY.y = rand() % 700 + 5;
                break;
            case UP: // if going up (coming from below)
                randomXY.x = rand() % 1700;
                randomXY.y = 870.f;
                break;
            case DOWN: // if going down (coming from above)
                randomXY.x = rand() % 800 + 5;
                randomXY.y = -50.f;
                break;
            default:
                break;
        }

    if (!overlapping) // if overlapping is false, then this is the first loop through the do while(), so find a slot for our randomWord
    {
        for (i = 0; wordVector.at(i).first.getString() != ""; ++i); // this finds the next empty wordVector slot
        wordVector.at(i).first.setString(randomWord);
        wordVector.at(i).second = d;
    }

    wordVector.at(i).first.setPosition(randomXY); // set the position to the random position we just generated

    for (long unsigned int v = 0; v < wordVector.size(); ++v) // and now check to see if any other words are going to overlap
    {
        if (wordVector.at(v).first.getString() != "")
        {
            if (v != i && (wordVector.at(v).first.getGlobalBounds().intersects(wordVector.at(i).first.getGlobalBounds())))
            {
                ++count; // if this is anything but zero it will loop again to get new randomly generated coordinates
            }
        }
    }

    if (count == 0) overlapping = false;
    else overlapping = true;

    } while (overlapping); // I'm sure this can be done better but I didn't think about this as a potential problem until after I saw it happen
}

void updateWords(std::vector<std::pair<sf::Text, Direction>> &wordVector, double speed)
{
    for (long unsigned int i = 0; i < wordVector.size(); ++i) // for each element in the wordVector
    {
        if (wordVector[i].first.getString() != "") // if it's not empty,
        {
            switch (wordVector[i].second) // update its speed dependent on the direction
            {
                case RIGHT:
                    wordVector[i].first.move(speed, 0);
                    break;
                case LEFT:
                    wordVector[i].first.move(-speed, 0);
                    break;
                case UP:
                    wordVector[i].first.move(0, -speed);
                    break;
                case DOWN:
                    wordVector[i].first.move(0, speed);
                    break;
                default:
                    break;
            }
        }
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

void loadGamePlay(sf::RenderWindow * window, sf::Sprite * background, std::array<sf::Text *, 5> &textArray, std::vector<std::pair<sf::Text, Direction>> &wordVector)
{
    window->clear();
    window->draw(*background);
    for (long unsigned int i = 0; i < textArray.size(); ++i) // prints all text
    {
        window->draw(*textArray[i]);
    }

    for (long unsigned int i = 0; i < wordVector.size(); ++i)
    {
        if (wordVector.at(i).first.getString() != "") window->draw(wordVector[i].first);
    }

    window->display();
}