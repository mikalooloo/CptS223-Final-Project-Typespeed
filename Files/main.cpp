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

    // *******BUTTONS*******
    // hex codes for normal: 770077 and 180066 clicked: 990099 and 0000dd
    sf::Vector2f buttonLocation(500.f, 75.f); 
    Button playbutton("Images/PlayButtonNormal.png","Images/PlayButtonHover.png",PLAY,buttonLocation);
    buttonLocation.y += 200;
    Button rulesbutton("Images/RulesButtonNormal.png","Images/RulesButtonHover.png",RULES,buttonLocation);
    buttonLocation.y += 200;
    Button optionsbutton("Images/OptionsButtonNormal.png","Images/OptionsButtonHover.png",OPTIONS,buttonLocation);
    buttonLocation.y += 200;
    Button exitbutton("Images/ExitButtonNormal.png","Images/ExitButtonHover.png",EXIT,buttonLocation);

    // *******FONTS*******
    sf::Font font;
    createText(&font, "Fonts/Seaside Resort Font.ttf");
    sf::Text text("Loading the gameplay...", font, 30);
    text.setPosition(30.0f, 30.0f);

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
                result = playbutton.checkClick(translated_pos, true); 
                if (result == NONE) result = rulesbutton.checkClick(translated_pos, true); // if result == NONE is there because otherwise it can overwrite a previous button
                if (result == NONE) result = optionsbutton.checkClick(translated_pos, true);
                if (result == NONE) result = exitbutton.checkClick(translated_pos, true);
            }
            else // otherwise, checking for hovering!
            {
                playbutton.checkClick(translated_pos, false);
                rulesbutton.checkClick(translated_pos, false);
                optionsbutton.checkClick(translated_pos, false);
                exitbutton.checkClick(translated_pos, false);
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
                loadMainMenu(&window, &playbutton, &rulesbutton, &optionsbutton, &exitbutton);
                break;
        }

    }
    return 0; 
}