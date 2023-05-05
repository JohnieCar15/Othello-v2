#include <SDL2/SDL.h>
#include <utility>
#include <vector>
#include <iostream>

enum Piece
{
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

class Board {
public:
    Board();
    ~Board();

    void init();
    void insertPiece(std::pair<int, int> coordinates);
    void drawBoard(SDL_Renderer *renderer);
    bool topLeft(int x, int y);
    bool top(int x, int y);
    bool topRight(int x, int y);
    bool right(int x, int y);
    bool bottomRight(int x, int y);
    bool bottom(int x, int y);
    bool bottomLeft(int x, int y);
    bool left(int x, int y);
    void flipPieces(int x, int y);
    void draw_move(SDL_Renderer * renderer, int centreX, int centreY, int radius);
    std::vector<std::pair<int, int>> availableMoves();

private:
    Piece grid[8][8];
    std::vector<std::pair<int, int>> moves;
};
