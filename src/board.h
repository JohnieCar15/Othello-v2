#include <SDL2/SDL.h>

class Board {
public:
    Board();
    ~Board();

    void init();
    void renderPiece(SDL_Renderer *renderer, std::pair<int, int> coordinates);
    void drawBoard(SDL_Renderer *renderer);

private:
    int grid[8][8];
};