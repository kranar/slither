#include <doctest/doctest.h>
#include <stdexcept>
#include "Slither/Board.hpp"

using namespace Slither;

TEST_CASE("Board constructor.") {
  auto board = Board(10, 20);
  CHECK(board.get_width() == 10);
  CHECK(board.get_height() == 20);
  for(auto y = 0; y < board.get_height(); ++y) {
    for(auto x = 0; x < board.get_width(); ++x) {
      CHECK(board.get(x, y) == Board::Cell::EMPTY);
    }
  }
}

TEST_CASE("Board set and get.") {
  auto board = Board(10, 10);
  board.set(5, 5, Board::Cell::HEAD);
  CHECK(board.get(5, 5) == Board::Cell::HEAD);
  board.set(5, 5, Board::Cell::EMPTY);
  CHECK(board.get(5, 5) == Board::Cell::EMPTY);
  board.set(0, 0, Board::Cell::APPLE);
  CHECK(board.get(0, 0) == Board::Cell::APPLE);
}

TEST_CASE("Board out of range") {
  auto board = Board(10, 10);
  CHECK_THROWS_AS(board.set(-1, 0, Board::Cell::HEAD), std::out_of_range);
  CHECK_THROWS_AS(board.set(10, 0, Board::Cell::HEAD), std::out_of_range);
  CHECK_THROWS_AS(board.set(0, -1, Board::Cell::HEAD), std::out_of_range);
  CHECK_THROWS_AS(board.set(0, 10, Board::Cell::HEAD), std::out_of_range);
  CHECK_THROWS_AS(board.get(-1, 0), std::out_of_range);
  CHECK_THROWS_AS(board.get(10, 0), std::out_of_range);
  CHECK_THROWS_AS(board.get(0, -1), std::out_of_range);
  CHECK_THROWS_AS(board.get(0, 10), std::out_of_range);
}
