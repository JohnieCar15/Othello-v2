#include "board.h"

Board::Board() {}
Board::~Board() {}


void Board::init() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = 0;
        }
    }
}