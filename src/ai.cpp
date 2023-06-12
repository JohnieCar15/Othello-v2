#include "ai.h"
#include <iostream>
Ai::Ai() {}
Ai::~Ai() {}


std::pair<int, int> Ai::randomMove(std::vector<std::pair<int, int>> moves) {
    size_t random_int = static_cast<size_t>(std::rand()) % moves.size();
    return moves.at(random_int);
}

// Returns optimal value for
// current player(Initially called
// for root and maximizer)
float Ai::alphaBeta(Board board, int depth, Piece maximizingPlayer, int alpha, int beta) {
    /*
    PSEUDO CODE

    function minimax(node, depth, alpha, beta, maximizingPlayer) is  
    if depth ==0 or node is a terminal node then  
    return static evaluation of node  
    
    if MaximizingPlayer then      // for Maximizer Player  
    maxEva= -infinity            
    for each child of node do  
        eva= minimax(child, depth-1, alpha, beta, False)  
        maxEva= max(maxEva, eva)   
        alpha= max(alpha, maxEva)      
        if beta<=alpha  
            break  
    return maxEva  
        
    else                         // for Minimizer player  
    minEva= +infinity   
    for each child of node do  
        eva= minimax(child, depth-1, alpha, beta, true)  
        minEva= min(minEva, eva)   
        beta= min(beta, eva)  
        if beta<=alpha  
            break          
    return minEva  
    
    */
   if (depth == 0) {
        return coinParity(board, maximizingPlayer) + mobility(board, maximizingPlayer) + corners(board, maximizingPlayer); 
   }

    
    (void) board;
    (void) depth;
    (void) maximizingPlayer;
    (void) alpha;
    (void) beta;
    return 0;
}



float Ai::coinParity(Board board, Piece p) {
    Piece (*grid)[8] = board.getGrid();
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

float Ai::mobility(Board board, Piece p) {
    Piece opp = (p == Piece::BLACK) ? Piece::WHITE : Piece::BLACK;
    std::vector<std::pair<int, int>> maxPlayer = board.availableMoves(p);
    std::vector<std::pair<int, int>> minPlayer = board.availableMoves(opp);
    float maxPlayerSize = static_cast<float>(maxPlayer.size());
    float minPlayerSize = static_cast<float>(minPlayer.size());
    if (maxPlayerSize + minPlayerSize != 0) {
        return (100 * (maxPlayerSize- minPlayerSize)) / (maxPlayerSize + minPlayerSize);
    }
    return 0;
}

float Ai::corners(Board board, Piece p) {
    Piece (*grid)[8] = board.getGrid();
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