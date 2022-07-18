#include <SFML/Graphics.hpp>
#include "../headers/Game.h"
#include <iostream>

int main()
{
	std::srand(static_cast<unsigned>(time(NULL)));
    Game game;

    // Game execution
    while (game.executing())
    {
        // Listen to events
		game.update();

		game.render();
        // Render the window and game
        
    }

    
    return 0;
}