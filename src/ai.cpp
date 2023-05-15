#include "ai.h"
#include <iostream>

Ai::Ai() {}
Ai::~Ai() {}


std::pair<int, int> Ai::randomMove(std::vector<std::pair<int, int>> &moves) {
    size_t random_int = static_cast<size_t>(std::rand()) % moves.size();
    return moves.at(random_int);
}

float Ai::coinParity(Piece (&grid)[8][8], Piece p) {
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

float Ai::corners(Piece (&grid)[8][8], Piece p) {
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