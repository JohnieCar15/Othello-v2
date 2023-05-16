#ifndef AI_H
#define AI_H

#include <SDL2/SDL.h>
#include <utility>
#include <cstdlib>
#include <vector>
#include <bits/stdc++.h>

#include "piece.h"

class Ai {
public:
    Ai();
    ~Ai();

    std::pair<int, int> randomMove(std::vector<std::pair<int, int>> &moves);
    int minimax(int depth, int nodeIndex, bool isMax, int scores[], int h);

    /* Captures difference in coins between max player and min player */
    float coinParity(Piece (&grid)[8][8], Piece p);
    float mobility(std::vector<std::pair<int, int>> &maxPlayer, std::vector<std::pair<int, int>> &minPlayer);
    float corners(Piece (&grid)[8][8], Piece p);
};

#endif 