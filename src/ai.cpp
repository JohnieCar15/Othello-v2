#include "ai.h"
#include <iostream>

Ai::Ai() {}
Ai::~Ai() {}


std::pair<int, int> Ai::randomMove(std::vector<std::pair<int, int>> moves) {
    size_t random_int = static_cast<size_t>(std::rand()) % moves.size();
    return moves.at(random_int);
}

int Ai::coinParity(Piece grid[8][8], Piece p) {
    int maxPlayer = 0;
    int minPlayer = 0;
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