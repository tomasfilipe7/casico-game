#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
/**
 * Class that contains the objects that will perform an animation when 
 *  the button "START" is pressed
 */

class Object
{
    public:
        // Constructor
        Object();
        Object(sf::Color objectColor, int size, sf::Color outline);
        ~Object();

        // Get the object
        sf::RectangleShape getObject();

        // Change object attributes
        void move(int x, int y);
        void changePosition(int x, int y);
        //Set size
        void setSize(int size);
        void scale(sf::Vector2f factor);
        void setScale(sf::Vector2f scale);

        //Change colors
        void changeFillColor(sf::Color color);
        void changeOutlineColor(sf::Color color);
    private:
        // Object reference
        sf::RectangleShape rectangle;
        
};