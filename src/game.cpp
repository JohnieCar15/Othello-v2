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

        ai = new Ai(board);

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
        case SDL_MOUSEBUTTONDOWN:
            if (SDL_BUTTON_LEFT == event.button.button) {
                std::pair p = coordinates();
                if (board->insertPiece(p, Piece::BLACK)) {
                    std::pair aip = ai->randomMove(board->availableMoves(Piece::WHITE));
                    board->insertPiece(aip, Piece::WHITE);
                    render();

                }
            } else if (SDL_BUTTON_RIGHT == event.button.button) {
                board->playMoves(5);
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

void Game::drawMove(int centreX, int centreY, int radius)
{
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
   const int diameter = (radius * 2);

   int x = (radius - 1);
   int y = 0;
   int tx = 1;
   int ty = 1;
   int error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }

   SDL_RenderPresent(renderer);
}

void Game::drawPiece(int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void Game::drawBoard() {
    Piece (*grid)[8] = board->getGrid();
    for (int i = 0; i < 8; i++) {
        // Fill in the columns
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == Piece::BLACK) {
                SDL_Color color;
                color.r = 0;
                color.g = 0;
                color.b = 0;
                drawPiece(50 + (100 * i), 50 + (100 * j), 40, color);
            } else if (grid[i][j] == Piece::WHITE) {
                SDL_Color color;
                color.r = 255;
                color.g = 255;
                color.b = 255;
                drawPiece(50 + (100 * i), 50 + (100 * j), 40, color);
            }
        }
    }

    // Note this is only for black
    for (std::pair<int, int> i : board->availableMoves(Piece::BLACK)) {
        drawMove(50 + (100 * i.first), 50 + (100 * i.second), 40);
    }


}

void Game::render() {
    SDL_RenderClear(renderer);
    // Draws background
    SDL_RenderCopy(renderer, background, NULL, NULL);
    // Draw pieces onto board
    drawBoard();

    std::pair scores = board->scores();
    std::cout << scores.first << " " << scores.second << "\n";
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