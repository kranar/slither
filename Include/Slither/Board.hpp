#ifndef SLITHER_BOARD_HPP
#define SLITHER_BOARD_HPP
#include <cstdint>
#include <vector>
#include "Slither/Slither.hpp"

namespace Slither {

  /** Represents a game board. */
  class Board {
    public:

      /** Enumerates the types of cells. */
      enum Cell : std::uint8_t {

        /** The cell is empty. */
        EMPTY,

        /** The cell contains the head of the snake. */
        HEAD,

        /** The cell contains the body of the snake. */
        BODY,

        /** The cell contains the tail of the snake. */
        TAIL,

        /** The cell contains an apple. */
        APPLE
      };

      /** Constructs an empty board. */
      Board(int width, int height);

      /** Returns the width of the board. */
      int get_width() const;

      /** Returns the height of the board. */
      int get_height() const;

      /**
       * Sets the cell at a given position, overwriting the previous cell.
       * @param x The x coordinate to set.
       * @param y The y coordinate to set.
       * @param cell The cell to write at the specified position.
       */
      void set(int x, int y, Cell cell);

      /**
       * Returns the cell at a given position.
       * @param x The x coordinate to get.
       * @param y The y coordinate to get.
       * @return The cell at the given position.
       */
      Cell get(int x, int y) const;

    private:
      int m_width;
      int m_height;
      std::vector<std::vector<Cell>> m_cells;
  };
}

#endif
