/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* main.cpp
*/
#include "header.h"
#include "Button.hpp"
#include "Settings.hpp"

struct desktop
{
    unsigned int width;
    unsigned int height;
};

int main(int argc, char * argv[])
{
    // *******WINDOW AND BACKGROUND*******
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktop), "Typespeed");
    window.setView(sf::View(sf::FloatRect(0,0,1850,900)));

    sf::Texture backgroundTexture;
    createAsset<sf::Texture>(&backgroundTexture, "Images/VaporwaveBackground.png");
    sf::Sprite background(backgroundTexture);
    background.setScale(0.725,0.65);

    // *******BUTTONS*******
    // MAIN MENU
    // 760x100: hex codes for normal: 770077 and 180066 clicked: 990099 and 0000dd
    sf::Vector2f buttonLocation(535.f, 75.f); 
    Button playbutton("Images/PlayButtonNormal.png","Images/PlayButtonHover.png",PLAY,buttonLocation);
    buttonLocation.y += 200;
    Button rulesbutton("Images/RulesButtonNormal.png","Images/RulesButtonHover.png",RULES,buttonLocation);
    buttonLocation.y += 200;
    Button optionsbutton("Images/OptionsButtonNormal.png","Images/OptionsButtonHover.png",OPTIONS,buttonLocation);
    buttonLocation.y += 200;
    Button exitbutton("Images/ExitButtonNormal.png","Images/ExitButtonHover.png",EXIT,buttonLocation);

    std::array<Button *, 4> buttonArray = { &playbutton, &rulesbutton, &optionsbutton, &exitbutton };

    // OPTIONS
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


    // *******TEXTS AND FONTS*******
    sf::Font font;
    createAsset<sf::Font>(&font, "Fonts/Seaside Resort Font.ttf");
    sf::Text text("", font, 30);
    text.setPosition(30.0f, 30.f); // top left

    // MAIN MENU
    sf::Text titletext("Typespeed", font, 80);
    titletext.setPosition(30.0f, 175.0f); // top left, title screen/main menu
    sf::Text subtitletext1("can you", font, 50);
    subtitletext1.setPosition(80.0f, 400.f); // underneath the title, for main menu
    sf::Text subtitletext2("keep up?", font, 50);
    subtitletext2.setPosition(100.0f, 475.f); // underneath the title, for main menu

    sf::Text creditstext1("Credits", font, 50);
    creditstext1.setPosition(1470.0f, 300.0f); // righthand side of main menu
    sf::Text creditstext2("Mikaela Dean", font, 35);
    creditstext2.setPosition(1445.0f, 375.0f); // righthand side of main menu
    sf::Text creditstext3("Sierra Svetlik", font, 35);
    creditstext3.setPosition(1445.0f, 425.0f); // righthand side of main menu

    std::array<sf::Text *,6> textArray = { &titletext, &subtitletext1, &subtitletext2, &creditstext1, &creditstext2, &creditstext3};

    // OPTIONS
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

    // *******MUSIC*******
    sf::Music mainMenuMusic;
    if (!mainMenuMusic.openFromFile("Music/Great Little Challenge.ogg")) throw std::runtime_error("Music failed to load");
    mainMenuMusic.play();

    // *******VARIABLES*******
    Settings settings(&optionsBArray, &optionsTArray);
    Action result = NONE;
    srand(time(0));

    // *******GAME IS RUNNING*******
    while (window.isOpen())
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (settings.getMusic() && mainMenuMusic.getStatus() == sf::SoundSource::Paused) mainMenuMusic.play();
        else if (!settings.getMusic() && mainMenuMusic.getStatus() == sf::SoundSource::Playing) mainMenuMusic.pause();

        // *******MOUSE POSITIONING*******
        if (result == NONE) // if currently in main menu, check to see where the mouse is
        {
            auto translated_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) // is something being clicked?
            {
                // then check if it was a button that was clicked
                for (long unsigned int i = 0; i < buttonArray.size() && result == NONE; ++i)
                {
                    result = buttonArray[i]->checkClick(translated_pos, true);
                }

            }
            else // otherwise, checking for hovering!
            {
                for (long unsigned int i = 0; i < buttonArray.size(); ++i)
                {
                    buttonArray[i]->checkClick(translated_pos, false);
                }
            }
        }
        else if (result == OPTIONS) // if currently in options, check to see where the mouse is
        {
            auto translated_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) // is something being clicked?
            {
                // then check if it was a button that was clicked
                // if settings.checkButtons() returns OPTIONS, then none of the buttons were clicked
                result = settings.checkButtons(true, translated_pos);

            }
            else // otherwise, checking for hovering!
            {
                settings.checkButtons(false, translated_pos);
            }
        }

        // *******MAIN MENU and BUTTONS*******
        switch (result) // currently all this does is puts up text that says it's loading the blank
        {
            case PLAY: 
                if(playbutton.getClickState() == CLICKED) text.setString("Loading the gameplay...");
                playbutton.setClickState(NORMALB);
                // COMBO TRACKER and sound effects
                gamePlay(window, font, settings);
                break;

            case RULES:
                if(rulesbutton.getClickState() == CLICKED) text.setString("Loading the rules...");
                rulesbutton.setClickState(NORMALB);

                window.clear();
                window.draw(text);
                window.display();
                break;

            case OPTIONS: case DIFF: case DIR: case MUS: case EFF:
                optionsbutton.setClickState(NORMALB);

                /* options: the option in () is the default option
                -gameplay options
                difficulty: (easy) - normal - hard
                text direction: (right) - left - up - down - all (automatically locks onto all if difficulty is set to hard)
                //word bank: remove - add - list (can remove, add, or see all of the words in any difficulty)
                -sound options
                music: (on) - off
                sound effects: (on) - off
                */
                result = settings.nextButton(result);

                settings.displayOptions(&window);
                break;
            case EXIT:
                window.close();
                break;

            case NONE: // if none, then it's the main menu
                loadMainMenu(&window, &background, buttonArray, textArray);
                break;
            default:
                result = NONE;
                break;
        }

    }

    return 0; 
}