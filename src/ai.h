#ifndef AI_H
#define AI_H

#include <SDL2/SDL.h>
#include <utility>
#include <cstdlib>
#include <vector>
#include <bits/stdc++.h>

#include "piece.h"

const int MAX = 1000;
const int MIN = -1000;

class Ai {
public:
    Ai();
    ~Ai();

    std::pair<int, int> randomMove(std::vector<std::pair<int, int>> &moves);
    int minimax(int depth, int nodeIndex, bool isMax, int scores[], int h);
    int alphaBeta(int depth, int nodeIndex, bool maximizingPlayer, int values[], int alpha, int beta);

    /* Captures difference in coins between max player and min player */
    float coinParity(Piece (&grid)[8][8], Piece p);
    float mobility(std::vector<std::pair<int, int>> &maxPlayer, std::vector<std::pair<int, int>> &minPlayer);
    float corners(Piece (&grid)[8][8], Piece p);
};

#endif 