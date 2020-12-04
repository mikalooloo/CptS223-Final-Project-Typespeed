/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Meeonka (?)
* 12/11/2020
* main.cpp
*/

#include "Button.hpp"

int main(int argc, char * argv[])
{
     sf::RenderWindow window(sf::VideoMode(1920, 1080), "Typespeed");
    // Buttons
    sf::Vector2f v1(16.5f, 24.f); 
    Button button1("Images/PlayButton.png","Images/PlayButtonClicked.png",v1);

    while (window.isOpen())
    {
        sf::Event event; 
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            //auto mouse_pos = sf::Mouse::getPosition(window);
            auto translated_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            button1.checkClick(translated_pos);
        }


        window.clear();
        window.draw(button1.getSprite());
        window.display();
    }
    return 0; 
}