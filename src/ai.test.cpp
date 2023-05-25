#include "ai.h"
#include "board.h"

#include <catch2/catch.hpp>

TEST_CASE("") {
    SECTION("Default") {
        Board *board = new Board();
        board->init();
        std::pair<int, int> scores = board->scores();
        REQUIRE(scores.first == 2);
        REQUIRE(scores.second == 2);
    }
}