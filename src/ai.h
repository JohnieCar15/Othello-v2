#ifndef AI_H
#define AI_H

#include <SDL2/SDL.h>
#include <utility>
#include <cstdlib>
#include <vector>

#include "piece.h"

class Ai {
public:
    Ai();
    ~Ai();

    std::pair<int, int> randomMove(std::vector<std::pair<int, int>> moves);
    std::pair<int, int> alphaBeta(std::vector<std::pair<int, int>> moves);

    /* Captures difference in coins between max player and min player */
    int coinParity(Piece grid[8][8], Piece p);
};

#endif 