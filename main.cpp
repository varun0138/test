#include <SFML/Graphics.hpp>
#include <iostream>

#include "gui/Button.hpp"
#include "gui/Checkbox.hpp"
#include "gui/Slider.hpp"

const float WINDOW_WIDTH = 1000.0f;
const float WINDOW_HEIGHT = 800.0f;

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "", sf::Style::Close | sf::Style::Titlebar);

    sf::Font font;
    font.loadFromFile("font.ttf");

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
            
        }

        
        window.clear(sf::Color(220,220,220,255));

  


        window.display();
    }

}