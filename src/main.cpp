#include <iostream>
#include <SDL2/SDL.h>
#include "othello.h"

Game *game = nullptr;

int main ( int argc, char *argv[] )
{
	(void) argc;
	(void) argv;

	game = new Game();
	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);
	SDL_Event event;
	SDL_PollEvent(&event);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();



	return 0;
}
