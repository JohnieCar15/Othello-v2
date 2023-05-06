#include <SDL2/SDL.h>
#include <utility>
#include <cstdlib>
#include <vector>

class Ai {
public:
    Ai();
    ~Ai();

    std::pair<int, int> randomMove(std::vector<std::pair<int, int>> moves);
    std::pair<int, int> alphaBeta(std::vector<std::pair<int, int>> moves);
};