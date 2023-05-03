#include "board.h"

Board::Board() {}
Board::~Board() {}


void Board::init() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = 0;
        }
    }
}

void draw_circle(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color)
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

void Board::drawBoard(SDL_Renderer *renderer) {
    (void) renderer;
}

void Board::renderPiece(SDL_Renderer *renderer, std::pair<int, int> coordinates) {
    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;

    int x = coordinates.first;
    int y = coordinates.second;

    grid[x][y] = 1;

    draw_circle(renderer, 50 + (100 * x), 50 + (100 * y), 40, color);
}


