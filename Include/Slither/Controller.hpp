#ifndef SLITHER_CONTROLLER_HPP
#define SLITHER_CONTROLLER_HPP
#include <cstdint>
#include <deque>
#include <random>
#include "Slither/Board.hpp"

namespace Slither {

  /** Represents the game controller that manages the game state. */
  class Controller {
    public:

      /** Represents the direction of the snake's movement. */
      enum class Direction : std::uint8_t {
        UP,
        DOWN,
        LEFT,
        RIGHT
      };

      /** Represents the game state. */
      enum class State : std::uint8_t {
        RUNNING,
        VICTORY,
        GAME_OVER
      };

      /** Constructs a game controller with an existing board. */
      explicit Controller(Board board);

      /** Returns the current game board. */
      const Board& get_board() const;

      /** Returns the current game state. */
      State get_state() const;

      /** Returns the current game score. */
      int get_score() const;

      /**
       * Updates the game state by moving the snake in the provided direction
       * and processing collisions. This method should be called periodically
       * to advance the game.
       * @param direction The direction for the snake to move in.
       * @return The updated state of the game.
       */
      State update(Direction direction);

    private:
      Board m_board;
      State m_state;
      int m_score;
      std::deque<std::pair<int, int>> m_snake_positions;
      std::mt19937 m_generator;

      void update_apple();
  };
}

#endif
