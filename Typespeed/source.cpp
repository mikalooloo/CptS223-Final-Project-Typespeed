/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* source.cpp
*
* Gameplay Music Credit to:
* https://patrickdearteaga.com
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

    // *******MUSIC AND SOUNDS*******
    sf::Music gamePlayMusic;
    if (!gamePlayMusic.openFromFile("Music/Intergalactic Odyssey.ogg")) throw std::runtime_error("Music failed to load");
    sf::Music gameOverMusic;
    if (!gameOverMusic.openFromFile("Music/I Miss You.ogg")) throw std::runtime_error("Music failed to load");

    if (settings.getMusic()) gamePlayMusic.play();
    gamePlayMusic.setVolume(50.f);
    gamePlayMusic.setLoop(true);
    gameOverMusic.setVolume(50.f);
    gameOverMusic.setLoop(true);

    sf::SoundBuffer correctWordBuffer;
    if (!correctWordBuffer.loadFromFile("Music/CorrectWordSound.wav")) throw std::runtime_error("Sound failed to load");
    sf::SoundBuffer wrongWordBuffer;
    if (!wrongWordBuffer.loadFromFile("Music/WrongWordSound.wav")) throw std::runtime_error("Sound failed to load");
    sf::SoundBuffer lostComboBuffer;
    if (!lostComboBuffer.loadFromFile("Music/LostComboSound.wav")) throw std::runtime_error("Sound failed to load");
    sf::SoundBuffer lostLifeBuffer;
    if (!lostLifeBuffer.loadFromFile("Music/LostLifeSound.wav")) throw std::runtime_error("Sound failed to load");

    sf::Sound correctWord(correctWordBuffer);
    sf::Sound wrongWord(wrongWordBuffer);
    sf::Sound lostCombo(lostComboBuffer);
    sf::Sound lostLife(lostLifeBuffer);


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

    // **FOR DISPLAYING DURING GAMEPLAY**
    std::array<sf::Text *, 5> textArray = { &playerText, &cpsText, &cpsNum, &comboText, &comboNum };

    std::vector<std::pair<sf::Text, Direction>> wordVector;

    for (int i = 0; i < 15; ++i) // makes 15 words so max 15 words on screen at a time
    {
        sf::Text word("",wordFont,30);
        wordVector.push_back(std::make_pair(word,RIGHT));
    }

    // **FOR DISPLAYING END GAME**
    sf::RectangleShape rectangle(sf::Vector2f(800.f,700.f)); // background rectangle
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::White);
    rectangle.setOutlineThickness(2);
    rectangle.setPosition(525.f,100.f);
    sf::RectangleShape comboRectangle(sf::Vector2f(250.f,150.f)); // behind the combo display
    comboRectangle.setFillColor(sf::Color::Black);
    comboRectangle.setOutlineColor(sf::Color::Magenta);
    comboRectangle.setOutlineThickness(3);
    comboRectangle.setPosition(800.f,345.f);

    sf::Text gameOver("Game Over", screenFont, 50);
    gameOver.setPosition(755.f, 150.f);
    sf::Text taunt("", wordFont, 25);
    randomTaunt(taunt);
    sf::Text timeLastedText("Time", screenFont, 35);
    timeLastedText.setPosition(600.f,325.f);
    sf::Text timeLastedNum("0", wordFont, 35);
    timeLastedNum.setPosition(605.f,380.f);

    Button mainMenuButton("Images/ReturnButtonNormal.png","Images/ReturnButtonHover.png",BACK,sf::Vector2f(680.f,570.f));
    Button exitButton("Images/LeaveButtonNormal.png","Images/LeaveButtonHover.png",EXIT,sf::Vector2f(800.f,670.f));

    // *******LIFE TRACKER*******
    sf::Texture lifeATexture;
    createAsset<sf::Texture>(&lifeATexture, "Images/StarLifeAlive.png");
    sf::Texture lifeDTexture;
    createAsset<sf::Texture>(&lifeDTexture, "Images/StarLifeDead.png");

    sf::Sprite lifeA1(lifeATexture);
    sf::Sprite lifeA2(lifeATexture);
    sf::Sprite lifeA3(lifeATexture);
    sf::Sprite lifeD1(lifeDTexture);
    sf::Sprite lifeD2(lifeDTexture);
    sf::Sprite lifeD3(lifeDTexture);

    std::array<sf::Sprite *, 3> lifeArray = { &lifeA1, &lifeA2, &lifeA3 }; // these will change to the dead versions when a life is lost
    std::array<sf::Sprite *, 3> deadArray = { &lifeD1, &lifeD2, &lifeD3 };

    float pos1 = 1550.f;
    for (int i = 0; i < 3; ++i) // for each sprite
    {
        lifeArray[i]->setScale(0.25, 0.25); 
        deadArray[i]->setScale(0.25, 0.25);
        lifeArray[i]->setPosition(pos1, 25.f);
        deadArray[i]->setPosition(pos1, 25.f);
        pos1 += 100.f;
    }

    // *******VARIABLES*******
    bool gameover = false;
    bool clicked; // for end of game, to see if a button has been clicked
    Action result = NONE; // for end of game, to see if a button has been clicked and if so what to do

    sf::String playerInput; // used to read player input during gameplay
    std::string playerKey = ""; // used to search hash table and helps keep track of # of correct characters
    std::string randomWord = "";

    int correctCharacters = 0; 
    double cps = 0.0; // correct characters per second
    std::string shortenString = ""; // used to shorten string to a certain decimal place (like cps)
    int highestCombo = 0;
    int combo = 0;
    bool correct = false; // if what the player typed was correct or not

    sf::Clock clock;
    sf::Clock overallTime;
    sf::Time endTime = sf::seconds(0);
    int seconds; // every this many seconds, a new word appears on the screen
    double speed; // how fast the words go

    int onscreen = 0; // how many words are onscreen
    int outofbounds = 0; // how many words became out of bounds and were removed
    int lives = 3; // how many lives the player has (once it reaches 0 the game ends)

    if (settings.getDifficulty() == EASY) 
    {
        seconds = 6; // the higher this number is, the easier it is
        speed = 0.5; // the lower this number is, the easier it is
    }
    else if (settings.getDifficulty() == NORMAL) 
    {
        seconds = 4;
        speed = 0.75;
    }
    else 
    {
        seconds = 2;
        speed = 1;
    }

    //********HASH TABLE*******
    std::ifstream infile;
    infile.open("Files/Words.csv");
    HashTable<std::string, int> *hash = new HashTable<std::string, int>(211); // size 211 because word count is 200* 2 = 200 and next prime is 211
    std::string word;
    while (getline(infile, word, ',')) hash->insert(std::make_pair(word,1));
    infile.close(); 

    overallTime.restart(); // restarting to get a more accurate time

    // *******GAMEPLAY*******
    while (window.isOpen())
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::TextEntered && !gameover) // if player is typing during the game
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

            // **CHECKING IF SOMETHING WAS CLICKED**
            auto translated_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left); // is something being clicked?
            // if so check which button if any was clicked, otherwise check for hovering
            result = mainMenuButton.checkClick(translated_pos, clicked);
            if (result == NONE) result = exitButton.checkClick(translated_pos, clicked);
            
        }

        if (!gameover) // while gameover is false, run the gameplay
        {
        
        if (settings.getMusic() && gamePlayMusic.getStatus() == sf::SoundSource::Paused) gamePlayMusic.play();
        else if (!settings.getMusic() && gamePlayMusic.getStatus() == sf::SoundSource::Playing) gamePlayMusic.pause();

        if (clock.getElapsedTime().asSeconds() > seconds && onscreen < 14) // if this is true, then we need to add a new word
        {
            ++onscreen;
            addNewWord(hash,wordVector,settings.getDirection());
            // if it's hard or it's normal and they have at least a combo of 10, add another word
            if (onscreen < 13 && (settings.getDifficulty() == HARD || (settings.getDifficulty() == NORMAL && combo > 10)))
            {
                addNewWord(hash,wordVector,settings.getDirection());
            }
            clock.restart();
        } 

        if (playerKey != "") // if playerKey is not "", then player has entered something
        {
            if (hash->at(playerKey) == ONSCREEN) // if what the player entered is actually ONSCREEN
            {
                if (settings.getSoundEffects()) correctWord.play();
                hash->setState(playerKey, VALID);
                --onscreen;
                correct = true;
                for (auto & v : wordVector) // reset the word in the wordVector so it stops printing it out
                {
                    if (v.first.getString() == playerKey)
                    {
                        v.first.setString("");
                        break;
                    }
                }

                increaseDifficulty(speed);
            }
            else // if not found in the hash table,
            {
                if (settings.getSoundEffects()) wrongWord.play();
                correct = false;
            }
            
            // if correct is true, adds to their combo and cps, if it's false then reset combo 
            updateComboCPS(correct,combo,highestCombo,comboNum,correctCharacters,cps,shortenString,cpsNum,overallTime,playerKey);
        }
        
        // updateWords updates the location of each word, and it returns how many become out of bounds (and erases those out of bound words from the vector)
        outofbounds = updateWords(wordVector, speed);
        if (outofbounds != 0) // this means at least 1 word went out of the bounds
        {
            if (settings.getSoundEffects()) lostLife.play();
            lives -= outofbounds; // remove a life for each word out of bounds
            updateLifeTracker(lifeArray, deadArray, outofbounds); // update the visual life tracker
            if (highestCombo < combo) highestCombo = combo;
            combo = 0; // reset combo
            comboNum.setString(std::to_string(combo));
            onscreen -= outofbounds; 
            outofbounds = 0; // reset
        }

        // check if game is over!
        if (lives < 1) gameover = true;

        background.update();
        loadGamePlay(&window, background.getSprite(), textArray, wordVector, lifeArray);
        } 
        else // this means gameplay is over, now the game over screen!
        {

            if (endTime.asSeconds() == 0) // if 0, then this is the first time in the game over screen, let's adjust some values
            {
                if (settings.getMusic())
                {
                    if (gamePlayMusic.getStatus() == sf::SoundSource::Playing) gamePlayMusic.stop();
                    gameOverMusic.play();
                }
                endTime = overallTime.restart(); // save final time
                shortenString = std::to_string(endTime.asSeconds());
                shortenString.erase(shortenString.begin()+4,shortenString.end()); // shortens the decimal
                timeLastedNum.setString(shortenString);

                // sets up the game over screen correctly, reusing some text used during gameplay
                cpsText.setCharacterSize(35);
                cpsText.setPosition(1160.f,325.f);
                cpsNum.setCharacterSize(35);
                cpsNum.setPosition(1165.f,380.f); 
                comboText.setCharacterSize(40);
                comboText.setPosition(840.f,355.f);
                comboNum.setCharacterSize(40);
                comboNum.setString(std::to_string(highestCombo));
                if (highestCombo < 9) comboNum.setPosition(910.f,410.f); // this way the combo looks nice
                else comboNum.setPosition(900.f,410.f); // and centered no matter if it's 2 digits or 1
            }


            switch (result) // based on what button is clicked
            {
                case BACK: // go back to Main Menu
                    return;
                    break;
                case EXIT: // exit the game
                    window.close();
                    break;
                default:
                    break;
            }

            // *******DISPLAYING GAME OVER*******
            window.clear();

            // backgrounds
            window.draw(*background.getSprite());
            window.draw(rectangle);
            window.draw(comboRectangle);

            // top titles
            window.draw(gameOver);
            window.draw(taunt);

            // scores
            window.draw(timeLastedText);
            window.draw(timeLastedNum);
            window.draw(cpsText);
            window.draw(cpsNum);
            window.draw(comboText);
            window.draw(comboNum);

            // buttons
            window.draw(mainMenuButton.getSprite());
            window.draw(exitButton.getSprite());
            
            window.display();
        }
        
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
                randomXY.x = -200.f;
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

int updateWords(std::vector<std::pair<sf::Text, Direction>> &wordVector, double speed)
{
    int outofbounds = 0;

    for (long unsigned int i = 0; i < wordVector.size(); ++i) // for each element in the wordVector
    {
        if (wordVector[i].first.getString() != "") // if it's not empty,
        {
            switch (wordVector[i].second) // update its speed dependent on the direction
            {
                case RIGHT:
                    wordVector[i].first.move(speed, 0);

                    if (wordVector[i].first.getGlobalBounds().left > 1845.f) // if out of bounds
                    {
                        ++outofbounds;
                        wordVector[i].first.setString(""); // erase
                    }
                    break;
                case LEFT:
                    wordVector[i].first.move(-speed, 0);

                    if (wordVector[i].first.getGlobalBounds().left + wordVector[i].first.getGlobalBounds().width < -50.f) // if out of bounds
                    {
                        ++outofbounds;
                        wordVector[i].first.setString(""); // erase
                    }
                    break;
                case UP:
                    wordVector[i].first.move(0, -speed);
                    if (wordVector[i].first.getGlobalBounds().top < -50.f) // if out of bounds
                    {
                        ++outofbounds;
                        wordVector[i].first.setString(""); // erase
                    }
                    break;
                case DOWN:
                    wordVector[i].first.move(0, speed);

                    if (wordVector[i].first.getGlobalBounds().top + wordVector[i].first.getGlobalBounds().height > 920.f) // if out of bounds
                    {
                        ++outofbounds;
                        wordVector[i].first.setString(""); // erase
                    }
                    break;
                default:
                    break;
            }
        }
    }

    return outofbounds;
}
void updateLifeTracker(std::array<sf::Sprite *, 3> &lifeArray, std::array<sf::Sprite *, 3> &deadArray, int liveslost)
{
    if (lifeArray[0] != deadArray[0] && liveslost != 0)
    {
        lifeArray[0] = deadArray[0]; // replaces the purple star with a gray one to show it's dead/gone
        --liveslost;
    }
    if (lifeArray[1] != deadArray[1] && liveslost != 0)
    {
        lifeArray[1] = deadArray[1];
        --liveslost;
    }
        if (lifeArray[2] != deadArray[2] && liveslost != 0)
    {
        lifeArray[2] = deadArray[2];
        --liveslost;
    }
}

void updateComboCPS(bool correct, int &combo, int &highestCombo, sf::Text &comboNum, int &correctCharacters, double &cps, std::string &cpsString, sf::Text &cpsNum, sf::Clock &clock, std::string &playerKey)
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
        if (highestCombo < combo) highestCombo = combo;
        combo = 0; // reset their combo
        comboNum.setString(std::to_string(combo));
    }

    playerKey = "";
}

void increaseDifficulty(double &speed)
{
    speed += 0.01;
}

void randomTaunt(sf::Text &taunt)
{
    int random = rand() % 6 + 1; // randomizing the taunt for the game over screen

    switch (random)
    {
        case 1:
            taunt.setString("I think even my grandma could do better than that!");
            taunt.setPosition(580.f,225.f);
            break;
        case 2:
            taunt.setString("Wow, and I thought I was bad!");
            taunt.setPosition(715.f,225.f);
            break;
        case 3:
            taunt.setString("That's amazing...ly bad for someone your age.");
            taunt.setPosition(620.f,225.f);
            break;
        case 4:
            taunt.setString("Did you even try?");
            taunt.setPosition(795.f,225.f);
            break;
        case 5:
            taunt.setString("Try an easier mode next time...");
            taunt.setPosition(715.f,225.f);
            break;
        case 6:
            taunt.setString("That was done quick!");
            taunt.setPosition(780.f,225.f);
            break;
    }
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

void loadGamePlay(sf::RenderWindow * window, sf::Sprite * background, std::array<sf::Text *, 5> &textArray, std::vector<std::pair<sf::Text, Direction>> &wordVector, std::array<sf::Sprite *, 3> &lifeArray)
{
    window->clear();
    window->draw(*background);
    for (long unsigned int i = 0; i < textArray.size(); ++i) // prints all text
    {
        window->draw(*textArray[i]);
    }

    for(long unsigned int i = 0; i < lifeArray.size(); ++i)
    {
        window->draw(*lifeArray[i]);
    }

    for (long unsigned int i = 0; i < wordVector.size(); ++i)
    {
        if (wordVector.at(i).first.getString() != "") window->draw(wordVector[i].first);
    }

    window->display();
}