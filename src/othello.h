#include <SDL2/SDL.h>

#include <iostream>

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


private:
    bool isRunning;
    SDL_Texture *texture;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *image;

};