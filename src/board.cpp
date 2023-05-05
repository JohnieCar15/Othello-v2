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

    moves = availableMoves();
    for (std::pair<int, int> i : moves) {
        // std::cout << i.first << " " << i.second << "\n";
        draw_move(renderer, 50 + (100 * i.first), 50 + (100 * i.second), 40);
    }


}

void Board::insertPiece(std::pair<int, int> coordinates) {
    bool flag = false;
    for (std::pair<int, int> p : moves) {
        if (p.first == coordinates.first && p.second == coordinates.second) {
            flag = true;
        }
    }

    if (!flag) return;

    int x = coordinates.first;
    int y = coordinates.second;

    grid[x][y] = Piece::BLACK;
    flipPieces(coordinates.first, coordinates.second);
}

bool Board::topLeft(int x, int y) {
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (grid[i][j] == Piece::BLACK) {
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

bool Board::top(int x, int y) {
    for (int i = x - 1; i >= 0; i--) {
        if (grid[i][y] == Piece::BLACK) {
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

bool Board::topRight(int x, int y) {
    for (int i = x - 1, j = y + 1; i >= 0 && j <= 7; i--, j++) {
        if (grid[i][j] == Piece::BLACK) {
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

bool Board::right(int x, int y) {
    for (int j = y + 1; j <= 7; j++) {
        if (grid[x][j] == Piece::BLACK) {
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

bool Board::bottomRight(int x, int y) {
    for (int i = x + 1, j = y + 1; i <= 7 && j <= 7; i++, j++) {
        if (grid[i][j] == Piece::BLACK) {
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

bool Board::bottom(int x, int y) {
    for (int i = x + 1; i <= 7; i++) {
        if (grid[i][y] == Piece::BLACK) {
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

bool Board::bottomLeft(int x, int y) {
    for (int i = x + 1, j = y - 1; i <= 7 && j >= 0; i++, j--) {
        if (grid[i][j] == Piece::BLACK) {
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

bool Board::left(int x, int y) {
    for (int j = y - 1; j >= 0; j--) {
        if (grid[x][j] == Piece::BLACK) {
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

std::vector<std::pair<int, int>> Board::availableMoves() {
    std::vector<std::pair<int, int>> moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (
                topLeft(i, j) ||
                top(i, j) ||
                topRight(i, j) ||
                right(i, j) ||
                bottomRight(i, j) ||
                bottom(i, j) ||
                bottomLeft(i, j) ||
                left(i, j)
            ) {
                std::pair p = std::make_pair(i, j);
                moves.push_back(p);
            }
        }
    }

    return moves;
}

void Board::flipPieces(int x, int y) {
    if (topLeft(x, y)) {
        for (int i = x - 1, j = y - 1; grid[i][j] != Piece::BLACK; i--, j--) {
            grid[i][j] = Piece::BLACK;
        }
    }

    if (top(x, y)) {
        for (int i = x - 1; grid[i][y] != Piece::BLACK; i--) {
            grid[i][y] = Piece::BLACK;
        }
    }

    if (topRight(x, y)) {
        for (int i = x - 1, j = y + 1; grid[i][j] != Piece::BLACK; i--, j++) {
            grid[i][j] = Piece::BLACK;
        }
    }

    if (right(x, y)) {
        for (int j = y + 1; grid[x][j] != Piece::BLACK; j++) {
            grid[x][j] = Piece::BLACK;
        }
    }

    if (bottomRight(x, y)) {
        for (int i = x + 1, j = y + 1; grid[i][j] != Piece::BLACK; i++, j++) {
            grid[i][j] = Piece::BLACK;
        }
    }


    if (bottom(x, y)) {
        for (int i = x + 1; grid[i][y] != Piece::BLACK; i++) {
            grid[i][y] = Piece::BLACK;
        }
    }

    if (bottomLeft(x, y)) {
        for (int i = x + 1, j = y - 1; grid[i][j] != Piece::BLACK; i++, j--) {
            grid[i][j] = Piece::BLACK;
        }
    }

    if (left(x, y)) {
        for (int j = y - 1; grid[x][j] != Piece::BLACK; j--) {
            grid[x][j] = Piece::BLACK;
        }
    }
}