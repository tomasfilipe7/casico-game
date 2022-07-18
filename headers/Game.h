#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../headers/Object.h"
#include "../headers/Button.h"
/**
 * Class that contains the Game, UI and System logic. 
 * 
 */

class Game
{
    // Functions
    private:
        // Initialization
        void initWindow();
        void initVariables();
        void initObjects();
        void initUI();
    public:
        // Constructors
        Game();
        virtual ~Game();

        //Update
        void update();
        void pollEvents();
        void updateActiveObjects();
        void updateUI();

        //Render 
        void render();
        void renderObjects();
        void renderUI();

        // Window management
        bool executing() const;

        // Game system
        void changeActiveObjects();
        void addCoin();
        void removeCoin();
        bool hasCoins();
        void startPlay();
        void pausePlay();

        //Getters
        int getCoins();
        int getPlays();

        //Button click verification
        bool isClickingOnStart();
        bool isClickingOnCreditsIn();
        bool isClickingOnCreditsOut();

    // Variables
    private:
        // Window and event
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event event;

        // Objects
        Object *objects;
        Object *activeObjects;
        sf::Vector2f firstObjectPos;
        sf::Vector2f secondObjectPos;
        sf::Vector2f thirdObjectPos;

        // Number of coins and plays
        int coins;
        int plays;

        //Animation
        float animationTime;
        float currentGameTime;
        bool playRunning;
        bool reducing_size;
        bool playStarted;
        int animationLoopCount;

        //Buttons
        Button startButton;
        Button creditsInButton;
        Button creditsOutButton;
        sf::Text coinText;
        sf::Text playsText;

        //Font
        sf::Font font;

    
};