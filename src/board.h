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
    void insertPiece(std::pair<int, int> coordinates, std::vector<std::pair<int, int>> moves, Piece p);
    void drawBoard(SDL_Renderer *renderer);
    bool topLeft(int x, int y, Piece p);
    bool top(int x, int y, Piece p);
    bool topRight(int x, int y, Piece p);
    bool right(int x, int y, Piece p);
    bool bottomRight(int x, int y, Piece p);
    bool bottom(int x, int y, Piece p);
    bool bottomLeft(int x, int y, Piece p);
    bool left(int x, int y, Piece p);
    void flipPieces(int x, int y, Piece p);
    void draw_move(SDL_Renderer * renderer, int centreX, int centreY, int radius);
    std::pair<int, int> scores();
    std::vector<std::pair<int, int>> availableMoves(Piece p);

private:
    Piece grid[8][8];
};
