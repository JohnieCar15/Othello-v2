#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"

Game *game = nullptr;

int main ( int argc, char *argv[] )
{
	(void) argc;
	(void) argv;

	game = new Game();
	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);
	// Render board with pieces
	game->render();
	while (game->running()) {

		game->handleEvents();
		// Display board with available moves
		// Take input from user
		// Find coordinates of click
		// Check if valid coordinates
		// Enter piece into grid
		// Flip pieces in between
		// Render to screen

		game->update();

	}

	game->clean();



	return 0;
}
