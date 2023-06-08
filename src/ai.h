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
    Ai(Board *board) :board_{board} {}
    ~Ai();

    std::pair<int, int> randomMove(std::vector<std::pair<int, int>> moves);
    int alphaBeta(Piece **board, int depth, Piece maximizingPlayer, int alpha, int beta);

    /* Captures difference in coins between max player and min player */
    float coinParity(Piece p);

    /* Captures relative mobility between number of moves between players */
    float mobility(Piece p);

    /* Corners are important since they can't be outflanked */
    float corners(Piece p);
private:
    /* Pointer to board that contains ai */
    Board *board_;
};

#endif