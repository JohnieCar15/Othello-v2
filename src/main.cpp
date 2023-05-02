#include <iostream>
#include <SDL2/SDL.h>
#include "game.h"

Game *game = nullptr;

int main ( int argc, char *argv[] )
{
	(void) argc;
	(void) argv;

	// const int FPS = 60;
	const Uint32 frameDelay = 1000 / 60;

	Uint32 frameStart;
	Uint32 frameTime;

	game = new Game();
	game->init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);
	while (game->running()) {
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();



	return 0;
}
