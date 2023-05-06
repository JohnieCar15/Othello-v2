#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <utility>

#include "board.h"
#include "ai.h"

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void render();
    void clean();
    void update();
    bool running() { return isRunning; }
    std::pair<int, int> coordinates();


private:
    bool isRunning;
    SDL_Texture *background;
    SDL_Window *window;
    SDL_Renderer *renderer;
    Board *board;
    Ai *ai;

};