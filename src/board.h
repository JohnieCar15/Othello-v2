#include <SDL2/SDL.h>

class Board {
public:
    Board();
    ~Board();

    void init();
    bool canFlip();


private:
    int grid[8][8];
};