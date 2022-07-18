// #pragma once

#include "../headers/Game.h"
#include "../headers/Object.h"
#include "../headers/Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
// #include <string> 

// Constructor
Game::Game()
{
    // Initialize the window, the variables, the animation objects and the UI.
    this->initWindow();
    this->initVariables();
    this->initObjects();
    this->initUI();
}

// Destructor
Game::~Game()
{
    // Delete the pointers
    delete this->window;
    delete[] this->objects;
    delete[] this->activeObjects;
}

/**
 * Initialize the variables needed for the game. These include:
 * Position of the objects, times for animation, booleans for the animation, ammout of plays and credits and loading the font
 * 
 */
void Game::initVariables()
{
    this->firstObjectPos = sf::Vector2f(100, this->window->getSize().y*0.40);
    this->secondObjectPos = sf::Vector2f(400, this->window->getSize().y*0.40);
    this->thirdObjectPos = sf::Vector2f(700, this->window->getSize().y*0.40);
    this->animationTime = 1000.f;
    this->currentGameTime = 0.f;
    this->reducing_size = true;
    this->animationLoopCount = 0;
    this->plays = 0;
    this->coins = 0;
    this->playStarted = false;
    
    // Verify if it is possible to load the font.
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

    // Start the game paused
    this->pausePlay();
}

/**
 * Initialize the window with a 800x600 size
 * 
 */
void Game::initWindow()
{
    this->window = nullptr;
    this->videoMode.width = 800;
    this->videoMode.height = 600;
    this->window = new sf::RenderWindow(this->videoMode, "Game");
}

/**
 * @brief Initialize the UI, which includes the three buttons and the two texts 
 * displaying the number of credits and plays
 * 
 */
void Game::initUI()
{
    //START button
    this->startButton = Button(sf::Color::Black, sf::Color::White, 30, "START");
    this->startButton.setFont();
    this->startButton.setPosition(sf::Vector2f(200, 400));
    this->startButton.setRectangle();

    //CREDITS IN button
    this->creditsInButton = Button(sf::Color::Black, sf::Color::White, 30, "CREDITS IN");
    this->creditsInButton.setFont();
    this->creditsInButton.setPosition(sf::Vector2f(400, 400));
    this->creditsInButton.setRectangle();

    //CREDITS OUT button
    this->creditsOutButton = Button(sf::Color::Black, sf::Color::White, 30, "CREDITS OUT");
    this->creditsOutButton.setFont();
    this->creditsOutButton.setPosition(sf::Vector2f(600, 400));
    this->creditsOutButton.setRectangle();
    //Credits text
    std::string coinString = "Credits: ";
    coinString += std::to_string(this->coins);
    this->coinText.setString(coinString);
    this->coinText.setColor(sf::Color::White);
    this->coinText.setCharacterSize(30);
    this->coinText.setFont(this->font);
    this->coinText.setPosition(sf::Vector2f(200 ,50));

    // //Plays text
    std::string playsString = "Plays: ";
    playsString += std::to_string(this->plays);
    this->playsText.setString(playsString);
    this->playsText.setColor(sf::Color::White);
    this->playsText.setCharacterSize(30);
    this->playsText.setFont(this->font);
    this->playsText.setPosition(sf::Vector2f(600 ,50));
}

/**
 * @brief Initialize the objects. 50 different objects(rectangles with a fillcolor and a outline color) will be created representing the possible objects
 *  that can be seen in the game. Another 3 will be created which will represent the 3 objects displayed on the screen and during the animation,
 *  the 3 active objects will change its appearance to match a random possible object.
 */
void Game::initObjects()
{
    // Possible colors to draw the rectangles/squares
    sf::Color _possibleColors[] = {sf::Color::Black, sf::Color::Blue, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta, sf::Color::Red, sf::Color::White, sf::Color::Yellow};

    this->objects = new Object[50];
    this->activeObjects = new Object[3];
    int object_index = 0;

    /**
     * @brief Two iterations will be made over the list of possible colors in order to create 50 different possible objects
     * with the combination of the different colors in the rectangle fill and outline
     * 
     */
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            // Create a square with 100 side size, _possibleColors[i] on the inside and _possibleColors[j] on the outline
            this->objects[object_index] = Object(_possibleColors[i], 100, _possibleColors[j]);
            object_index += 1;

            // If 50 objects were created, finish the loops
            if(object_index >= 50)
            {
                break;
            }
        }
        if(object_index >= 50)
        {
            break;
        }
    }
    
    // Initialize the active objects
    for (size_t i = 0; i < 3; i++)
    {
        this->activeObjects[i] = Object(sf::Color::White, 100, sf::Color::Black);
    }
    
    // Move the active objects to their positions
    this->activeObjects[0].changePosition(firstObjectPos.x, firstObjectPos.y);
    this->activeObjects[1].changePosition(secondObjectPos.x, secondObjectPos.y);
    this->activeObjects[2].changePosition(thirdObjectPos.x, thirdObjectPos.y);
    
    // Change the active objects to random possible objects
    this->changeActiveObjects();

}

/**
 * @brief Check if the game is executing
 * 
 * @return true 
 * @return false 
 */
bool Game::executing() const
{
    return this->window->isOpen();
}

/**
 * @brief Starts the objects animation.
 * 
 */
void Game::startPlay()
{
    // Play, if the animation will start and the user has enough coins
    if(!this->playStarted && this->hasCoins())
    {
        this->playRunning = true;
        this->playStarted = true;
        this->removeCoin();
    }
    // Resume if the animation had already started (means the game is only pause), then there is no need to remove coins.
    else if(this->playStarted)
    {
        this->playRunning = true;
    }
}

/**
 * @brief Stops the animation
 * 
 */
void Game::pausePlay()
{
    this->playRunning = false;
}

/**
 * @brief Changes the fill and outline colors of the active objects to the colors of three random possible objects
 * 
 */
void Game::changeActiveObjects()
{
    for (size_t i = 0; i < 3; i++)
    {
        Object _object = this->objects[rand() % 50];
        this->activeObjects[i].changeFillColor(_object.getObject().getFillColor()); 
        this->activeObjects[i].changeOutlineColor(_object.getObject().getOutlineColor()); 
        
    }
    
} 

/**
 * @brief Verify if mouse is over the START button
 * 
 * @return true 
 * @return false 
 */
bool Game::isClickingOnStart()
{
    return this->startButton.getRectangle().getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
}

/**
 * @brief Verify if mouse is over the CREDITS IN button
 * 
 * @return true 
 * @return false 
 */
bool Game::isClickingOnCreditsIn()
{
    return this->creditsInButton.getRectangle().getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
}


/**
 * @brief Verify if mouse is over the CREDITS OUT button
 * 
 * @return true 
 * @return false 
 */
bool Game::isClickingOnCreditsOut()
{
    return this->creditsOutButton.getRectangle().getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
}


/**
 * @brief Verify if the user has coins
 * 
 * @return true 
 * @return false 
 */
bool Game::hasCoins()
{
    return this->coins > 0;
}

/**
 * @brief Add a coin
 * 
 */
void Game::addCoin()
{
    this->coins += 1;
}

/**
 * @brief Remove a coin
 * 
 */
void Game::removeCoin()
{
    if(this->hasCoins())
    {
        this->coins -= 1;
    }
}

/**
 * @brief Listen to any events. It listens when the window is closed or when the user clicks with the mouse.
 * If the mouse clicked it will be verified if it clicked on a button and execute the respective action
 * 
 */
void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {

        switch (this->event.type)
        {
        case sf::Event::Closed:
        // If the user click on the close window button, close the window
            this->window->close();
            break;
        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Button::Left)
            {
                // If the user clicked on START, if the animation is running, pause it, otherwise, verify if it can play it.
                if(this->isClickingOnStart())
                {
                    if(this->playRunning)
                    {
                        this->pausePlay();
                    }
                    else
                    {
                        this->startPlay();
                    }
                }
                // If the user clicked on CREDITS IN, add a coin.
                else if(this->isClickingOnCreditsIn())
                {
                    this->addCoin();
                }
                // If the user clicked on CREDITS IN, remove a coin.
                else if(this->isClickingOnCreditsOut())
                {
                    this->removeCoin();
                }
            }
            
            break;
        default:
            break;
        }
            
    }
}

/**
 * @brief Update the active objects animation. The animation consists of:
 * At each play, the three objects will reduce its size and then grow bigger again, but with different colors. After five times repeating this process,
 * the objects will return to its "END OF PLAY" state and will remain with their last acquired colors. 
 * 
 */
void Game::updateActiveObjects()
{
    // Define the animation tick
    if(this->currentGameTime >= this->animationTime)
    {
        // Resets the time count
        this->currentGameTime = 0;

        // If the object is on reducing the size state, reduce its size
        if(this->reducing_size)
        {
            this->activeObjects[0].scale(sf::Vector2f(0.6f, 0.6f));
            this->activeObjects[1].scale(sf::Vector2f(0.6f, 0.6f));
            this->activeObjects[2].scale(sf::Vector2f(0.6f, 0.6f));
        }
        // Otherwise, increase it
        else
        {
            
            this->activeObjects[0].scale(sf::Vector2f(1.4f, 1.4f));
            this->activeObjects[1].scale(sf::Vector2f(1.4f, 1.4f));
            this->activeObjects[2].scale(sf::Vector2f(1.4f, 1.4f));
        }
        
        // If the animation already looped five times, it goes to the "END OF PLAY" state, the animation is marked as finish
        // and the number of plays increases by 1
        if(animationLoopCount >= 5 && !this->reducing_size && this->activeObjects[0].getObject().getScale().x <= 1.1f && this->activeObjects[0].getObject().getScale().x >= 0.9f)
        {
            //Do nothing
            this->activeObjects[0].setScale(sf::Vector2f(1.f,1.f));
            this->activeObjects[1].setScale(sf::Vector2f(1.f,1.f));
            this->activeObjects[2].setScale(sf::Vector2f(1.f,1.f));
            this->animationLoopCount = 0;
            this->reducing_size = true;
            this->plays += 1;
            this->playStarted = false;
            this->pausePlay();
            
            
        }
        // If the object is reducing size and is already small enough, change its colors and starts the enlargement animation
        else if(this->reducing_size && this->activeObjects[0].getObject().getScale().x <= 0.1f)
        {
            /// Complete reducing+
            this->reducing_size = false;
            this->changeActiveObjects();
            this->animationLoopCount += 1;
        }
        // If the object is increasing size and is already big enough,starts the reducing animation
        else if(!this->reducing_size && this->activeObjects[0].getObject().getScale().x >= 1.3f)
        {
            /// Complete augmenting
            this->reducing_size = true;
        }
        
    }
    else
    {
        // Adds the time
        this->currentGameTime +=1.f;
    }
    
    
}

/**
 * @brief Update the text with the number of plays and credits
 * 
 */
void Game::updateUI()
{
    std::string coinString = "Credits: ";
    coinString += std::to_string(this->coins);
    this->coinText.setString(coinString);

    std::string playsString = "Plays: ";
    playsString += std::to_string(this->plays);
    this->playsText.setString(playsString);
}


/**
 * @brief The main loop of the game.
 * 
 */
void Game::update()
{
    this->pollEvents();
    if(this->playRunning)
    {
        this->updateActiveObjects();
    }
    else
    {
        // this->updateActiveObjects();
    }
    updateUI();
    // this->activeObjects->getObject().move(sf::Vector2f(10000.f, 0.f));
}

/**
 * @brief Render the three active objects on the screen
 * 
 */
void Game::renderObjects()
{
    for (size_t i = 0; i < 3; i++)
    {
        this->window->draw(this->activeObjects[i].getObject());
    }
    
}

/**
 * @brief Renders the three buttons and the text containing the credits and the plays.
 * 
 */
void Game::renderUI()
{
    this->window->draw(this->startButton.getRectangle());
    this->window->draw(this->startButton.getText());

    this->window->draw(this->creditsInButton.getRectangle());
    this->window->draw(this->creditsInButton.getText());

    this->window->draw(this->creditsOutButton.getRectangle());
    this->window->draw(this->creditsOutButton.getText());

    this->window->draw(this->playsText);
    this->window->draw(this->coinText);
}

/**
 * @brief Clears the previous window and renders the game on the screen
 * 
 */
void Game::render()
{
    this->window->clear(sf::Color(37,150,190,255));

    
    this->renderUI();
    this->renderObjects();

    this->window->display();
}




    