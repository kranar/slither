#include <doctest/doctest.h>
#include <stdexcept>
#include "Slither/Controller.hpp"

using namespace Slither;

TEST_SUITE("Controller") {
  TEST_CASE("constructor") {
    auto initial_board = Board(16, 16);
    initial_board.set(5, 0, Board::Cell::HEAD);
    initial_board.set(4, 0, Board::Cell::BODY);
    initial_board.set(3, 0, Board::Cell::BODY);
    initial_board.set(2, 0, Board::Cell::TAIL);
    initial_board.set(6, 0, Board::Cell::APPLE);
    auto controller = Controller(initial_board);
    CHECK(controller.get_state() == Controller::State::RUNNING);
    auto& board = controller.get_board();
    CHECK(board.get_width() == 16);
    CHECK(board.get_height() == 16);
    CHECK(board.get(5, 0) == Board::Cell::HEAD);
    CHECK(board.get(4, 0) == Board::Cell::BODY);
    CHECK(board.get(3, 0) == Board::Cell::BODY);
    CHECK(board.get(2, 0) == Board::Cell::TAIL);
    CHECK(board.get(6, 0) == Board::Cell::APPLE);
  }

  TEST_CASE("update") {
    auto initial_board = Board(16, 16);
    auto center_x = initial_board.get_width() / 2;
    auto center_y = initial_board.get_height() / 2;
    initial_board.set(center_x, center_y, Board::Cell::HEAD);
    initial_board.set(center_x - 1, center_y, Board::Cell::BODY);
    initial_board.set(center_x - 2, center_y, Board::Cell::BODY);
    initial_board.set(center_x - 3, center_y, Board::Cell::TAIL);
    auto controller = Controller(initial_board);

    SUBCASE("move_up") {
      controller.update(Controller::Direction::UP);
      auto& updated_board = controller.get_board();
      CHECK(updated_board.get(center_x, center_y - 1) == Board::Cell::HEAD);
      CHECK(updated_board.get(center_x, center_y) == Board::Cell::BODY);
      CHECK(updated_board.get(center_x - 1, center_y) == Board::Cell::BODY);
      CHECK(updated_board.get(center_x - 2, center_y) == Board::Cell::TAIL);
    }

    SUBCASE("move_down") {
      controller.update(Controller::Direction::DOWN);
      auto& updated_board = controller.get_board();
      CHECK(updated_board.get(center_x, center_y + 1) == Board::Cell::HEAD);
      CHECK(updated_board.get(center_x, center_y) == Board::Cell::BODY);
      CHECK(updated_board.get(center_x - 1, center_y) == Board::Cell::BODY);
      CHECK(updated_board.get(center_x - 2, center_y) == Board::Cell::TAIL);
    }

    SUBCASE("move_right") {
      controller.update(Controller::Direction::RIGHT);
      auto& updated_board = controller.get_board();
      CHECK(updated_board.get(center_x + 1, center_y) == Board::Cell::HEAD);
      CHECK(updated_board.get(center_x, center_y) == Board::Cell::BODY);
      CHECK(updated_board.get(center_x - 1, center_y) == Board::Cell::BODY);
      CHECK(updated_board.get(center_x - 2, center_y) == Board::Cell::TAIL);
    }

    SUBCASE("collide_top") {
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::UP) ==
        Controller::State::GAME_OVER);
    }

    SUBCASE("collide_bottom") {
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::GAME_OVER);
    }

    SUBCASE("collide_left") {
      CHECK(controller.update(Controller::Direction::DOWN) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::LEFT) ==
        Controller::State::GAME_OVER);
    }

    SUBCASE("collide_right") {
      CHECK(controller.update(Controller::Direction::RIGHT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::RIGHT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::RIGHT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::RIGHT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::RIGHT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::RIGHT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::RIGHT) ==
        Controller::State::RUNNING);
      CHECK(controller.update(Controller::Direction::RIGHT) ==
        Controller::State::GAME_OVER);
    }
  }
}
