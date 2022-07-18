#include "../headers/Object.h"

/**
 * @brief Construct a new Object:: Object object. Initializes the rectangle with a fill color, side size and outline color
 * 
 * @param solidColor 
 * @param size 
 * @param outline 
 */
Object::Object(sf::Color solidColor, int size, sf::Color outline)
{
    this->rectangle.setSize(sf::Vector2f(size, size));
    this->rectangle.setOutlineColor(outline);
    this->rectangle.setOutlineThickness(size/10.f);
    this->rectangle.setFillColor(solidColor);
    this->rectangle.setOrigin(sf::Vector2f(this->rectangle.getSize().x/2, this->rectangle.getSize().y/2));
}

/**
 * @brief Construct a new Object:: Object object without arguments
 * 
 */
Object::Object()
{
    this->rectangle.setSize(sf::Vector2f(20, 20));
    this->rectangle.setOutlineColor(sf::Color::Black);
    this->rectangle.setOutlineThickness(2.f);
    this->rectangle.setFillColor(sf::Color::White);
}

/**
 * @brief Destroy the Object:: Object object
 * 
 */
Object::~Object()
{
}

/**
 * @brief Getter for the rectangle
 * 
 * @return sf::RectangleShape 
 */
sf::RectangleShape Object::getObject()
{
    return this->rectangle;
}

/**
 * @brief Change the object position
 * 
 * @param x 
 * @param y 
 */
void Object::changePosition(int x, int y)
{
    this->rectangle.setPosition(x, y);
}

/**
 * @brief Move the rectangle by offsetting its current position with an input vector
 * 
 * @param x 
 * @param y 
 */
void Object::move(int x, int y)
{
    this->rectangle.move(x, y);
}

/**
 * @brief Change the absolute rectangle size
 * 
 * @param size 
 */
void Object::setSize(int size)
{
    this->rectangle.setSize(sf::Vector2f(size, size));
}

/**
 * @brief Changes the scale of the rectangle by multiplying it by factor input.
 * 
 * @param factor 
 */
void Object::scale(sf::Vector2f factor)
{
    this->rectangle.scale(factor);
}

/**
 * @brief Change the scale value of the rectangle
 * 
 * @param scale 
 */
void Object::setScale(sf::Vector2f scale)
{
    this->rectangle.setScale(scale);
}

/**
 * @brief Change the rectangle fill color
 * 
 * @param color 
 */
void Object::changeFillColor(sf::Color color)
{
    this->rectangle.setFillColor(color);
}

/**
 * @brief Change the rectangle outline color
 * 
 * @param color 
 */
void Object::changeOutlineColor(sf::Color color)
{
    this->rectangle.setOutlineColor(color);
}