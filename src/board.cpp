#include "board.h"

Board::Board() {}
Board::~Board() {}


void Board::init() {
    /*
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 2 1 0 0 0
    0 0 0 1 2 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    0 0 0 0 0 0 0 0
    */

    // Fill in the rows
    for (int i = 0; i < 8; i++) {
        // Fill in the columns
        for (int j = 0; j < 8; j++) {
            if (i == 3 && j == 3) {
                grid[i][j] = Piece::WHITE;
            } else if (i == 3 && j == 4) {
                grid[i][j] = Piece::BLACK;
            } else if (i == 4 && j == 3) {
                grid[i][j] = Piece::BLACK;
            } else if (i == 4 && j == 4) {
                grid[i][j] = Piece::WHITE;
            } else {
                grid[i][j] = Piece::EMPTY;
            }
        }
    }
}

void draw_piece(SDL_Renderer *renderer, int x, int y, int radius, SDL_Color color)
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

void Board::draw_move(SDL_Renderer * renderer, int centreX, int centreY, int radius)
{
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

void Board::drawBoard(SDL_Renderer *renderer) {
    for (int i = 0; i < 8; i++) {
        // Fill in the columns
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == Piece::BLACK) {
                SDL_Color color;
                color.r = 0;
                color.g = 0;
                color.b = 0;
                draw_piece(renderer, 50 + (100 * i), 50 + (100 * j), 40, color);
            } else if (grid[i][j] == Piece::WHITE) {
                SDL_Color color;
                color.r = 255;
                color.g = 255;
                color.b = 255;
                draw_piece(renderer, 50 + (100 * i), 50 + (100 * j), 40, color);
            }
        }
    }

    // Note this is only for black
    for (std::pair<int, int> i : availableMoves(Piece::BLACK)) {
        draw_move(renderer, 50 + (100 * i.first), 50 + (100 * i.second), 40);
    }


}

void Board::insertPiece(std::pair<int, int> coordinates, std::vector<std::pair<int, int>> moves, Piece p) {
    bool flag = false;
    for (std::pair<int, int> move : moves) {
        if (move.first == coordinates.first && move.second == coordinates.second) {
            flag = true;
        }
    }

    if (!flag) return;

    int x = coordinates.first;
    int y = coordinates.second;

    grid[x][y] = p;
    flipPieces(coordinates.first, coordinates.second, p);
}

bool Board::topLeft(int x, int y, Piece p) {
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (grid[i][j] == p) {
            if (i == x - 1) {
                return false;
            } else {
                return true;
            }
        } else if (grid[i][j] == Piece::EMPTY) {
            return false;
        }
    }
    return false;
}

bool Board::top(int x, int y, Piece p) {
    for (int i = x - 1; i >= 0; i--) {
        if (grid[i][y] == p) {
            if (i == x - 1) {
                return false;
            } else {
                return true;
            }
        } else if (grid[i][y] == Piece::EMPTY) {
            return false;
        }
    }
    return false;
}

bool Board::topRight(int x, int y, Piece p) {
    for (int i = x - 1, j = y + 1; i >= 0 && j <= 7; i--, j++) {
        if (grid[i][j] == p) {
            if (i == x - 1) {
                return false;
            } else {
                return true;
            }
        } else if (grid[i][j] == Piece::EMPTY) {
            return false;
        }
    }
    return false;
}

bool Board::right(int x, int y, Piece p) {
    for (int j = y + 1; j <= 7; j++) {
        if (grid[x][j] == p) {
            if (j == y + 1) {
                return false;
            } else {
                return true;
            }
        } else if (grid[x][j] == Piece::EMPTY) {
            return false;
        }
    }
    return false;
}

bool Board::bottomRight(int x, int y, Piece p) {
    for (int i = x + 1, j = y + 1; i <= 7 && j <= 7; i++, j++) {
        if (grid[i][j] == p) {
            if (i == x + 1) {
                return false;
            } else {
                return true;
            }
        } else if (grid[i][j] == Piece::EMPTY) {
            return false;
        }
    }
    return false;
}

bool Board::bottom(int x, int y, Piece p) {
    for (int i = x + 1; i <= 7; i++) {
        if (grid[i][y] == p) {
            if (i == x + 1) {
                return false;
            } else {
                return true;
            }
        } else if (grid[i][y] == Piece::EMPTY) {
            return false;
        }
    }
    return false;
}

bool Board::bottomLeft(int x, int y, Piece p) {
    for (int i = x + 1, j = y - 1; i <= 7 && j >= 0; i++, j--) {
        if (grid[i][j] == p) {
            if (i == x + 1) {
                return false;
            } else {
                return true;
            }
        } else if (grid[i][j] == Piece::EMPTY) {
            return false;
        }
    }
    return false;
}

bool Board::left(int x, int y, Piece p) {
    for (int j = y - 1; j >= 0; j--) {
        if (grid[x][j] == p) {
            if (j == y - 1) {
                return false;
            } else {
                return true;
            }
        } else if (grid[x][j] == Piece::EMPTY) {
            return false;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> Board::availableMoves(Piece p) {
    std::vector<std::pair<int, int>> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (
                topLeft(i, j, p) ||
                top(i, j, p) ||
                topRight(i, j, p) ||
                right(i, j, p) ||
                bottomRight(i, j, p) ||
                bottom(i, j, p) ||
                bottomLeft(i, j, p) ||
                left(i, j, p)
            ) {
                std::pair move = std::make_pair(i, j);
                moves.push_back(move);
            }
        }
    }

    return moves;
}

void Board::flipPieces(int x, int y, Piece p) {
    if (topLeft(x, y, p)) {
        for (int i = x - 1, j = y - 1; grid[i][j] != p; i--, j--) {
            grid[i][j] = p;
        }
    }

    if (top(x, y, p)) {
        for (int i = x - 1; grid[i][y] != p; i--) {
            grid[i][y] = p;
        }
    }

    if (topRight(x, y, p)) {
        for (int i = x - 1, j = y + 1; grid[i][j] != p; i--, j++) {
            grid[i][j] = p;
        }
    }

    if (right(x, y, p)) {
        for (int j = y + 1; grid[x][j] != p; j++) {
            grid[x][j] = p;
        }
    }

    if (bottomRight(x, y, p)) {
        for (int i = x + 1, j = y + 1; grid[i][j] != p; i++, j++) {
            grid[i][j] = p;
        }
    }


    if (bottom(x, y, p)) {
        for (int i = x + 1; grid[i][y] != p; i++) {
            grid[i][y] = p;
        }
    }

    if (bottomLeft(x, y, p)) {
        for (int i = x + 1, j = y - 1; grid[i][j] != p; i++, j--) {
            grid[i][j] = p;
        }
    }

    if (left(x, y, p)) {
        for (int j = y - 1; grid[x][j] != p; j--) {
            grid[x][j] = p;
        }
    }
}