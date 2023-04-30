#include "othello.h"

Game::Game() {};
Game::~Game() {};

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

    uint32_t flags = 0;
    if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;


    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Game has started" << "\n";
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window) {
            std::cout << "Window created" << "\n";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer created" << "\n";
        }
        isRunning = true;

        image = SDL_LoadBMP("Board.png");
        if (!image) {
            std::cout << SDL_GetError() << "\n";
        }
        texture = SDL_CreateTextureFromSurface(renderer, image);
        if (texture) {
            std::cout << "Texture successfully loaded" << "\n";
        }

    } else {
        isRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            std::cout << "Mouse was pressed" << "\n";
            break;
        default:
            break;
    }
}

void Game::render() {
    // SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << "\n";
}

void Game::update() {}