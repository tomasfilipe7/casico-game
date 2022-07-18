#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
/**
 * Class that contains the Buttons used in the game.
 * 
 */

class Button
{
    //Functions
    public:
        // Constructor
        Button();
        Button(sf::Color ButtonColor, sf::Color textColor, int textSize, std::string text);
        ~Button();

        // Getters
        sf::RectangleShape getRectangle();
        sf::Text getText();

        // Attribute setters
        void setFont();
        void setRectangle();
        void setPosition(sf::Vector2f position);

    //Variables
    public:
        // Font
        sf::Font font;
    private:
        //Button components
        sf::RectangleShape rectangle;
        sf::Text text;
        
};