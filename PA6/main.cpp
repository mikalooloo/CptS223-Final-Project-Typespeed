/*
* CPTS223 PA 6
* Mikaela Dean and Sierra Svetlik (?)
* 12/11/2020
*/
#include <iostream>
#include <SFML/Graphics.hpp>
int main(int argc, char * argv[])
{
    std::string test = "political";
    //float dx, dy;
    float xspeed = 5, yspeed = 5;

    //render window
    sf::RenderWindow window(sf::VideoMode(500, 400), "Typespeed");
    window.setFramerateLimit(30);

    //set font
    sf::Font font;
    font.loadFromFile("NotoSansCJK-Bold.ttc");

    //test text
    sf::Text text("", font);
    text.setFont(font);
    text.setString("Test");
    text.setFillColor(sf::Color::Blue);
    text.setCharacterSize(50);
    text.setPosition(30, 200);

    sf::Text text2("", font);
    text2.setFont(font);
    text2.setFillColor(sf::Color::Red);
    text2.setCharacterSize(10);
    text.setPosition(20, 200);

    //make rectangle
    /*sf::RectangleShape rect(sf::Vector2f(30, 200));
    rect.setFillColor(sf::Color::Transparent)*/

    /*while(window.isOpen()){
        sf::Vector2f tPos = text.getPosition();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(tPos.x > 0){
                //text.move(-yspeed, tPos.x);
                text.move(-yspeed, 0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(tPos.x < 400){
                text.move(yspeed, 0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(tPos.y > 0){
                text.move(0, -xspeed);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(tPos.y < 350){
                text.move(0, xspeed);
            }
        }
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        test = "y position: " + std::to_string(tPos.y);
        text2.setString(test);

        window.clear();
        window.draw(text);
        window.draw(text2);
        window.display();
    }*/

    return 0;
}