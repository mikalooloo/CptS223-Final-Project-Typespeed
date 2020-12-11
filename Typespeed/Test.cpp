/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* Test.cpp
*/
#include "Test.hpp"
#include "Button.hpp"
#include "hash.h"
#include "Settings.hpp"

#include <iostream>
#include <fstream>

/* 
Test ID: Settings Difficulty and Direction Buttons test
Unit: Settings::nextButton for Difficulty and Direction
Description: test to determine if each button in Settings works correctly
Test steps:
1.     Create window object, as well as button and text arrays needed to initialize the Settings object
2.     Create a Settings object
3.     In a while window is open loop, display the Settings screen and check for button clicks
4.     Click the Difficulty button and print the current Difficulty before and after to the terminal
5.     Evaluate if the before Difficulty was Easy (0) and the after Difficulty was Normal (1)
6.     Click the Direction button 4 times, printing the before and after Direction each time
7.     Evalute if the prints follow the pattern of Right (0) to Left (1), Left (1) to Up (2), Up (2) to Down (3), Down (3) to Right (0)
8.     Now click the Difficulty button again, printing the current Difficulty before and after to the terminal
9.     Evaluate if the before Difficulty was Normal (1) and the after Difficulty was Hard (2), as well as if the Direction is now All (4)
10.    While Difficulty is on Hard, click the Direction button, printing the current Direction before and after to the terminal
11.    Evaluate if the before and after Direction was All (4)
Test data: Settings buttons and text arrays in main.cpp
Precondition: Settings explicit constructor works, Settings checkButtons works, createAsset works: Difficulty is on Easy, Direction is on Right
Postcondition: Difficulty is on Hard, Direction is on All
Expected result: Difficulty goes from Easy to Normal to Hard, Direction goes from Right to Left to Up to Down, and then to All while Difficulty is on Hard
Actual result: Difficulty goes from Easy to Normal to Hard, Direction goes from Right to Left to Up to Down, and then to All while Difficulty is on Hard
Status: passed
*/
void testSettingsDD(void)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop), "Typespeed");
    window.setView(sf::View(sf::FloatRect(0,0,1850,900)));

    sf::Vector2f buttonLocation(535.f, 75.f); 

    buttonLocation.x = 300.f; buttonLocation.y = 300.f;
    Button easyButton("Images/EasyButtonNormal.png","Images/EasyButtonHover.png",DIFF,buttonLocation);
    Button normalButton("Images/NormalButtonNormal.png","Images/NormalButtonHover.png",DIFF,buttonLocation);
    Button hardButton("Images/HardButtonNormal.png","Images/HardButtonHover.png",DIFF,buttonLocation);
    buttonLocation.x = 300.f; buttonLocation.y = 600.f;
    Button rightButton("Images/RightButtonNormal.png","Images/RightButtonHover.png",DIR,buttonLocation);
    Button leftButton("Images/LeftButtonNormal.png","Images/LeftButtonHover.png",DIR,buttonLocation);
    Button upButton("Images/UpButtonNormal.png","Images/UpButtonHover.png",DIR,buttonLocation);
    Button downButton("Images/DownButtonNormal.png","Images/DownButtonHover.png",DIR,buttonLocation);
    Button allButton("Images/AllButton.png", "Images/AllButton.png",DIR,buttonLocation);
    buttonLocation.x = 1350.f; buttonLocation.y = 300.f;
    Button musicButton("Images/MusicButtonNormal.png","Images/MusicButtonHover.png",MUS,buttonLocation);
    Button nomusicButton("Images/NoMusicButtonNormal.png","Images/NoMusicButtonHover.png",MUS,buttonLocation);
    buttonLocation.x = 1350.f; buttonLocation.y = 600.f;
    Button soundeffectsButton("Images/SoundEffectsButtonNormal.png","Images/SoundEffectsButtonHover.png",EFF,buttonLocation);
    Button nosoundeffectsButton("Images/NoSoundEffectsButtonNormal.png","Images/NoSoundEffectsButtonHover.png",EFF,buttonLocation);
    buttonLocation.x = 800.f; buttonLocation.y = 600.f;
    Button backButton("Images/BackButtonNormal.png","Images/BackButtonHover.png",BACK,buttonLocation);

    std::array<Button *, 13> optionsBArray = { &easyButton, &normalButton, &hardButton, &rightButton, &leftButton, &upButton, &downButton, &allButton, &musicButton, &nomusicButton, &soundeffectsButton, &nosoundeffectsButton, &backButton };

    sf::Font font;
    createAsset<sf::Font>(&font, "Fonts/Seaside Resort Font.ttf");

    sf::Text optionstext("Options", font, 80);
    optionstext.setPosition(725.f,50.f);
    sf::Text gameplaytext("Gameplay", font, 60);
    gameplaytext.setPosition(220.f, 150.f);
    sf::Text difftext("change difficulty", font, 30);
    difftext.setPosition(220.f, 260.f);
    sf::Text dirtext("change direction", font, 30);
    dirtext.setPosition(220.f, 560.f);
    sf::Text soundtext("Sound", font, 60);
    soundtext.setPosition(1320.f, 150.f);
    sf::Text mustext("toggle music", font, 30);
    mustext.setPosition(1320.f, 260.f);
    sf::Text efftext("toggle sound effects", font, 30);
    efftext.setPosition(1250.f, 560.f);

    std::array<sf::Text *, 7> optionsTArray = { &optionstext, &gameplaytext, &difftext, &dirtext, &soundtext, &mustext, &efftext };


    Settings settings(&optionsBArray, &optionsTArray);
    bool clicked;
    Action result = NONE;

    Difficulty oldDif = settings.getDifficulty();
    Direction oldDir = settings.getDirection();

    while (window.isOpen())
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

        // *******MOUSE POSITIONING*******
        auto translated_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left); // is something being clicked?

        result = settings.checkButtons(translated_pos, clicked);
        } 

        result = settings.nextButton(result);
        settings.displayOptions(&window);

        if (oldDif != settings.getDifficulty())
        {
            std::cout << "Before: " << oldDif << " and After: " << settings.getDifficulty() << std::endl;
            oldDif = settings.getDifficulty();
        }

        if (oldDir != settings.getDirection())
        {
            std::cout << "Before: " << oldDir << " and After: " << settings.getDirection() << std::endl;
            oldDir = settings.getDirection();
        }
    }
}

/* 
Test ID: Settings Music and Sound Effects Buttons test
Unit: Settings::nextButton for Music and Sound Effects
Description: test to determine if each button in Music and Sound Effects works correctly
Test steps:
1.    Create window object, as well as button and text arrays needed to initialize the Settings object
2.    Create a Settings object and a Music object, starting the music
3.    In a while window is open loop, display the Settings screen and check for button clicks
4.    Click the Music button and evaluate if the button changes correctly and the music stops
5.    Click the Sound Effects button and print out the before and after to the terminal
6.    Evaluate if the before Sound Effects was on (1) and the after was off (0)
Test data: Settings buttons and text arrays in main.cpp
Precondition: Settings explicit constructor works, Settings checkButtons works, createAsset works: Music is on, Sound Effects are on
Postcondition: Music is off, Sound Effects are off
Expected result: Music is off with the correct button image, Sound Effects are off with the correct button image
Actual result: Music is off with the correct button image, Sound Effects are off with the correct button image
Status: passed
*/
void testSettingsMSE(void)
{
     sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop), "Typespeed");
    window.setView(sf::View(sf::FloatRect(0,0,1850,900)));

    sf::Vector2f buttonLocation(535.f, 75.f); 

    buttonLocation.x = 300.f; buttonLocation.y = 300.f;
    Button easyButton("Images/EasyButtonNormal.png","Images/EasyButtonHover.png",DIFF,buttonLocation);
    Button normalButton("Images/NormalButtonNormal.png","Images/NormalButtonHover.png",DIFF,buttonLocation);
    Button hardButton("Images/HardButtonNormal.png","Images/HardButtonHover.png",DIFF,buttonLocation);
    buttonLocation.x = 300.f; buttonLocation.y = 600.f;
    Button rightButton("Images/RightButtonNormal.png","Images/RightButtonHover.png",DIR,buttonLocation);
    Button leftButton("Images/LeftButtonNormal.png","Images/LeftButtonHover.png",DIR,buttonLocation);
    Button upButton("Images/UpButtonNormal.png","Images/UpButtonHover.png",DIR,buttonLocation);
    Button downButton("Images/DownButtonNormal.png","Images/DownButtonHover.png",DIR,buttonLocation);
    Button allButton("Images/AllButton.png", "Images/AllButton.png",DIR,buttonLocation);
    buttonLocation.x = 1350.f; buttonLocation.y = 300.f;
    Button musicButton("Images/MusicButtonNormal.png","Images/MusicButtonHover.png",MUS,buttonLocation);
    Button nomusicButton("Images/NoMusicButtonNormal.png","Images/NoMusicButtonHover.png",MUS,buttonLocation);
    buttonLocation.x = 1350.f; buttonLocation.y = 600.f;
    Button soundeffectsButton("Images/SoundEffectsButtonNormal.png","Images/SoundEffectsButtonHover.png",EFF,buttonLocation);
    Button nosoundeffectsButton("Images/NoSoundEffectsButtonNormal.png","Images/NoSoundEffectsButtonHover.png",EFF,buttonLocation);
    buttonLocation.x = 800.f; buttonLocation.y = 600.f;
    Button backButton("Images/BackButtonNormal.png","Images/BackButtonHover.png",BACK,buttonLocation);

    std::array<Button *, 13> optionsBArray = { &easyButton, &normalButton, &hardButton, &rightButton, &leftButton, &upButton, &downButton, &allButton, &musicButton, &nomusicButton, &soundeffectsButton, &nosoundeffectsButton, &backButton };

    sf::Font font;
    createAsset<sf::Font>(&font, "Fonts/Seaside Resort Font.ttf");

    sf::Text optionstext("Options", font, 80);
    optionstext.setPosition(725.f,50.f);
    sf::Text gameplaytext("Gameplay", font, 60);
    gameplaytext.setPosition(220.f, 150.f);
    sf::Text difftext("change difficulty", font, 30);
    difftext.setPosition(220.f, 260.f);
    sf::Text dirtext("change direction", font, 30);
    dirtext.setPosition(220.f, 560.f);
    sf::Text soundtext("Sound", font, 60);
    soundtext.setPosition(1320.f, 150.f);
    sf::Text mustext("toggle music", font, 30);
    mustext.setPosition(1320.f, 260.f);
    sf::Text efftext("toggle sound effects", font, 30);
    efftext.setPosition(1250.f, 560.f);

    std::array<sf::Text *, 7> optionsTArray = { &optionstext, &gameplaytext, &difftext, &dirtext, &soundtext, &mustext, &efftext };


    Settings settings(&optionsBArray, &optionsTArray);
    bool clicked;
    Action result = NONE;

    sf::Music mainMenuMusic;
    if (!mainMenuMusic.openFromFile("Music/Great Little Challenge.ogg")) throw std::runtime_error("Music failed to load");
    mainMenuMusic.play();
    mainMenuMusic.setLoop(true);

    bool oldMus = settings.getMusic();
    bool oldSE = settings.getSoundEffects();

    while (window.isOpen())
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

        // *******MOUSE POSITIONING*******
        auto translated_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left); // is something being clicked?

        result = settings.checkButtons(translated_pos, clicked);
        } 

        result = settings.nextButton(result);
        settings.displayOptions(&window);

        if (oldSE != settings.getSoundEffects())
        {
            std::cout << "Before: " << oldSE << " and After: " << settings.getSoundEffects() << std::endl;
            oldSE = settings.getSoundEffects();
        }
    }

}

/* 
Test ID: Hash Table initialize test
Unit: Hash class
Description: test to determine if the hash table properly was made
Test steps:
1.    Create a hash table using Files/Words.csv
2.    Print out the hash table using print_hash()
3.    Evaluate if there are 100 words in the terminal
Test data: HashTable class and Words.csv
Precondition: hash table has not been made
Postcondition: hash table has been made and 100 words have been printed to the terminal
Expected result: 100 words have been printed to the terminal
Actual result: 100 words have been printed to the terminal
Status: passed
*/
void testHashTable(void)
{
    std::ifstream infile;
    infile.open("Files/Words.csv");
    HashTable<std::string, int> *hash = new HashTable<std::string, int>(211);
    std::string word;
    while (getline(infile, word, ',')) hash->insert(std::make_pair(word,1));
    infile.close(); 

    hash->print_hash();
}

/* 
Test ID: Hash Table find word test
Unit: Hash class, primarily at()
Description: test to determine if a word can be found in the hash table and if a word not found be correctly reported as not found
Test steps:
1.    Create a hash table using Files/Words.csv
2.    Search for the word "INFORMATION": it should be found
3.    Conditionally evaluate if the word was found
4.    Search for the word "DOG": it should not be found
5.    Conditionally evaluate if the word was found
Test data: HashTable class and Words.csv
Precondition: Hash Table insert works: hash table has not been made
Postcondition: hash table has been made, "INFORMATION" was found but "DOG" was not
Expected result: "INFORMATION" was found, "DOG" was not
Actual result: "INFORMATOIN" was found, "DOG" was not
Status: passed
*/
void testFindWord(void)
{
    std::ifstream infile;
    infile.open("Files/Words.csv");
    HashTable<std::string, int> *hash = new HashTable<std::string, int>(211);
    std::string word;
    while (getline(infile, word, ',')) hash->insert(std::make_pair(word,1));
    infile.close(); 

    if (hash->at("INFORMATION") == VALID)
    {
        std::cout << "INFORMATION was found - test part 1 passed" << std::endl;

        if (hash->at("DOG") != VALID) std::cout << "DOG was not found - test part 2 passed" << std::endl; 
        else std::cout << "DOG was found - test part 2 failed" << std::endl;
    }
    else
    {
        std::cout << "INFORMATION was not found - test part 1 failed, exiting test" << std::endl;
    }

}

/* 
Test ID: Life Tracker test
Unit: updateLifeTracker() in source.cpp
Description: test to determine if the images properly update in the lifeArray
Test steps:
1.    Create lifeArray and deadArray using Images/
2.    Call updateLifeTracker() and input lifeArray, deadArray, and 1
3.    Conditionally evaluate if lifeArray[0] is equal to deadArray[0]
4.    Call updateLifeTracker() again and input lifeArray, deadArray, and 2
5.    Conditionally evaluate if each index of lifeArray is equal to each index of deadArray
Test data: lifeArray and deadArray with Images/
Precondition: createAsset works: lifeArray is filled with lifeA and deadArray is filled with lifeD
Postcondition: lifeArray is filled with lifeD and deadArray is filled with lifeD
Expected result: lifeArray[0] is lifeD, then all of lifeArray is lifeD
Actual result: lifeArray[0] is lifeD, then all of lifeArray is lifeD
Status: passed
*/
void testLifeTracker(void)
{
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

    std::array<sf::Sprite *, 3> lifeArray = { &lifeA1, &lifeA2, &lifeA3 }; 
    std::array<sf::Sprite *, 3> deadArray = { &lifeD1, &lifeD2, &lifeD3 };

    updateLifeTracker(lifeArray, deadArray, 1);

    if (lifeArray[0] == deadArray[0])
    {
        std::cout << "lifeArray[0] is equal to deadArray[0] - test part 1 passed" << std::endl;

        updateLifeTracker(lifeArray, deadArray, 2);
        if (lifeArray[1] == deadArray[1] && lifeArray[2] == deadArray[2]) std::cout << "all of lifeArray is equal to all of deadArray - test part 2 passed" << std::endl; 
        else std::cout << "not all of lifeArray was equal to all of deadArray - test part 2 failed" << std::endl;
    }
    else
    {
        std::cout << "lifeArray[0] is not equal to deadArray[0] - test part 1 failed, exiting test" << std::endl;
    }
    
}