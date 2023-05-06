#include "game.h"

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

        const char *path = "../images/Board.bmp";
        SDL_Surface *image = SDL_LoadBMP(path);
        background = SDL_CreateTextureFromSurface(renderer, image);
        SDL_FreeSurface(image);
        if (background) {
            std::cout << "Background loaded" << "\n";
        }

        board = new Board();
        board->init();

        ai = new Ai();

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
            clean();
            break;
        // case SDL_MOUSEMOTION:
        //     int x, y;
        //     SDL_GetMouseState(&x, &y);
        //     std::cout << x << " " << y << "\n";
        //     break;

        case SDL_MOUSEBUTTONDOWN:
            if (SDL_BUTTON_LEFT == event.button.button) {
                std::pair p = coordinates();
                board->insertPiece(p, Piece::BLACK);
                std::pair aip = ai->randomMove(board->availableMoves(Piece::WHITE));
                board->insertPiece(aip, Piece::WHITE);
                render();
                std::cout << "Mouse click" << "\n";
            }
            break;
        default:
            break;
    }
}


std::pair<int, int> Game::coordinates() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    float xf = static_cast<float>(x) / 100;
    float yf = static_cast<float>(y) / 100;

    std::pair p = std::make_pair(floor(xf), floor(yf));

    return p;
}

void Game::render() {
    SDL_RenderClear(renderer);
    // Draws background
    SDL_RenderCopy(renderer, background, NULL, NULL);
    // Draw pieces onto board
    board->drawBoard(renderer);
    /* TODO: Draw available moves */
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyTexture(background);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << "\n";
}

void Game::update() {

}