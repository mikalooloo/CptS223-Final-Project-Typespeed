/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik
* 12/11/2020
* main.cpp
*/

#include "Button.hpp"

int main(int argc, char * argv[])
{
    // *******WINDOW*******
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Typespeed");
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("Images/VaporwaveBackground.png")) throw std::runtime_error("Texture failed to load");
    sf::Sprite background(backgroundTexture);
    background.setScale(0.725,0.65);

    // *******BUTTONS*******
    // hex codes for normal: 770077 and 180066 clicked: 990099 and 0000dd
    sf::Vector2f buttonLocation(535.f, 75.f); 
    Button playbutton("Images/PlayButtonNormal.png","Images/PlayButtonHover.png",PLAY,buttonLocation);
    buttonLocation.y += 200;
    Button rulesbutton("Images/RulesButtonNormal.png","Images/RulesButtonHover.png",RULES,buttonLocation);
    buttonLocation.y += 200;
    Button optionsbutton("Images/OptionsButtonNormal.png","Images/OptionsButtonHover.png",OPTIONS,buttonLocation);
    buttonLocation.y += 200;
    Button exitbutton("Images/ExitButtonNormal.png","Images/ExitButtonHover.png",EXIT,buttonLocation);

    std::array<Button *, 4> buttonArray = { &playbutton, &rulesbutton, &optionsbutton, &exitbutton };

    // *******TEXTS AND FONTS*******
    sf::Font font;
    createText(&font, "Fonts/Seaside Resort Font.ttf");
    sf::Text text("", font, 30);
    text.setPosition(30.0f, 30.f); // top left

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

    // *******VARIABLES*******
    MenuAction result = NONE;

    // *******GAME IS RUNNING*******
    while (window.isOpen())
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

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

        // *******MAIN MENU and BUTTONS*******
        switch (result) // currently all this does is puts up text that says it's loading the blank
        {
            case PLAY: 
                if(playbutton.getClickState() == CLICKED) text.setString("Loading the gameplay...");
                playbutton.setClickState(NORMAL);

                window.clear();
                window.draw(text);
                window.display();
                break;

            case RULES:
                if(rulesbutton.getClickState() == CLICKED) text.setString("Loading the rules...");
                rulesbutton.setClickState(NORMAL);

                window.clear();
                window.draw(text);
                window.display();
                break;

            case OPTIONS:
                if(optionsbutton.getClickState() == CLICKED) text.setString("Loading the options...");
                optionsbutton.setClickState(NORMAL);

                window.clear();
                window.draw(text);
                window.display();
                break;

            case EXIT:
                window.close();
                break;

            case NONE: // if none, then it's the main menu
                loadMainMenu(&window, &background, buttonArray, textArray);
                break;
        }

    }
    return 0; 
}