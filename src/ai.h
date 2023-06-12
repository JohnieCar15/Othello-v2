#ifndef AI_H
#define AI_H

#include <SDL2/SDL.h>
#include <utility>
#include <cstdlib>
#include <vector>
#include <bits/stdc++.h>

#include "piece.h"
#include "board.h"

const int MAX = 1000;
const int MIN = -1000;

class Ai {
public:
    Ai();
    ~Ai();

    std::pair<int, int> randomMove(std::vector<std::pair<int, int>> moves);
    float alphaBeta(Board board, int depth, Piece maximizingPlayer, int alpha, int beta);

    /* Captures difference in coins between max player and min player */
    float coinParity(Board board, Piece p);

    /* Captures relative mobility between number of moves between players */
    float mobility(Board board, Piece p);

    /* Corners are important since they can't be outflanked */
    float corners(Board board, Piece p);
};

#endif