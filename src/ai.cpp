#include "ai.h"
#include <iostream>

Ai::~Ai() {}


std::pair<int, int> Ai::randomMove(std::vector<std::pair<int, int>> &moves) {
    size_t random_int = static_cast<size_t>(std::rand()) % moves.size();
    return moves.at(random_int);
}

// Returns optimal value for
// current player(Initially called
// for root and maximizer)
int Ai::alphaBeta(Piece **board, int depth, bool maximizingPlayer, int alpha, int beta) {
    (void) board;
    (void) depth;  
    (void) maximizingPlayer;
    (void) alpha;
    (void) beta;
    return 0;
}



float Ai::coinParity(Piece p) {
    Piece (*grid)[8] = board_->getGrid();
    float maxPlayer = 0;
    float minPlayer = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j] == p) {
                maxPlayer++;
            } else if (grid[i][j] != Piece::EMPTY) {
                minPlayer++;
            }
        }
    }

    return (100 * (maxPlayer - minPlayer)) / (maxPlayer - minPlayer);

}

float Ai::mobility(std::vector<std::pair<int, int>> &maxPlayer, std::vector<std::pair<int, int>> &minPlayer) {
    float maxPlayerSize = static_cast<float>(maxPlayer.size());
    float minPlayerSize = static_cast<float>(minPlayer.size());
    if (maxPlayerSize + minPlayerSize != 0) {
        return (100 * (maxPlayerSize- minPlayerSize)) / (maxPlayerSize + minPlayerSize);
    }
    return 0;
}

float Ai::corners(Piece p) {
    Piece (*grid)[8] = board_->getGrid();
    float maxPlayer = 0;
    float minPlayer = 0;

    if (grid[0][0] == p) {
        maxPlayer++;
    } else if (grid[0][0] != Piece::EMPTY) {
        minPlayer++;
    }

    if (grid[0][7] == p) {
        maxPlayer++;
    } else if (grid[0][0] != Piece::EMPTY) {
        minPlayer++;
    }

    if (grid[7][0] == p) {
        maxPlayer++;
    } else if (grid[0][0] != Piece::EMPTY) {
        minPlayer++;
    }

    if (grid[7][7] == p) {
        maxPlayer++;
    } else if (grid[0][0] != Piece::EMPTY) {
        minPlayer++;
    }

    if (maxPlayer + minPlayer != 0) {
        return (100 * (maxPlayer - minPlayer)) / (maxPlayer + minPlayer);
    }
    return 0;
}