#include "../headers/Button.h"
#include <iostream>
#include <algorithm>
#include <unistd.h>
// #include "Ai"

/**
 * @brief Construct a new Button:: Button object. It includes the initialization of the text properties and the color of the rectangle.
 * It also reads the font file.
 * 
 * @param buttonColor 
 * @param textColor 
 * @param textSize 
 * @param text 
 */

// int getDirectory()
// {
//     char pBuf[256];
//     size_t len = sizeof(pBuf); 
//     int bytes = std::min(readlink("/proc/self/exe", pBuf, len), len - 1);
//     if(bytes >= 0)
//         pBuf[bytes] = '\0';
//     return bytes;
// }
Button::Button(sf::Color buttonColor, sf::Color textColor, int textSize, std::string text)
{
    
    this->rectangle.setFillColor(buttonColor);
    this->text.setString(text);
    this->text.setColor(textColor);
    this->text.setCharacterSize(textSize);
    

    if (this->font.loadFromFile("../include/Arialn.ttf"))
    {
        std::cout << "Font loaded successfully\n";
    }
    else if(this->font.loadFromFile("include/Arialn.ttf"))
    {
        std::cout << "Font loaded successfully\n";
    }
    else
    {
        std::cout << "Error loading fonts\n";
    }
    
}

/**
 * @brief Construct a new Button:: Button object without specifing attributes
 * 
 */
Button::Button()
{
    this->rectangle.setSize(sf::Vector2f(20, 20));
    this->rectangle.setOutlineColor(sf::Color::Black);
    this->rectangle.setOutlineThickness(2.f);
    this->rectangle.setFillColor(sf::Color::White);
}

/**
 * @brief Destroy the Button:: Button object
 * 
 */
Button::~Button()
{
}

/**
 * @brief Getter of the rectangle
 * 
 * @return sf::RectangleShape 
 */
sf::RectangleShape Button::getRectangle()
{
    return this->rectangle;
}
/**
 * @brief Getter of the text
 * 
 * @return sf::Text 
 */
sf::Text Button::getText()
{
    return this->text;
}

/**
 * @brief Assign the font to the text
 * 
 */
void Button::setFont()
{
    this->text.setFont(this->font);
}

/**
 * @brief Set the size of the rectangle
 * 
 */
void Button::setRectangle()
{
    // this->text.setOrigin(this->rectangle.getSize().x,this->rectangle.getSize().y);
    this->rectangle.setSize(sf::Vector2f(this->text.getGlobalBounds().width + 10, this->text.getGlobalBounds().height + 10));
}

/**
 * @brief Change the button position
 * 
 * @param position 
 */
void Button::setPosition(sf::Vector2f position)
{
    this->text.setOrigin((this->text.getLocalBounds().left + this->text.getLocalBounds().width)/2,(this->text.getLocalBounds().top + this->text.getLocalBounds().height)/2);
    
    this->text.setPosition(position);
    this->rectangle.setPosition(sf::Vector2f(this->text.getGlobalBounds().left - 5, this->text.getGlobalBounds().top - 5));
}