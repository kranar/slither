#include "Slither/Board.hpp"
#include <stdexcept>

using namespace Slither;

Board::Board(int width, int height)
  : m_width(width),
    m_height(height),
    m_cells(m_height, std::vector<Cell>(m_width, EMPTY)) {}

int Board::get_width() const {
  return m_width;
}

int Board::get_height() const {
  return m_height;
}

void Board::set(int x, int y, Cell cell) {
  if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
    m_cells[y][x] = cell;
  } else {
    throw std::out_of_range("Invalid x or y position");
  }
}

Board::Cell Board::get(int x, int y) const {
  if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
    return m_cells[y][x];
  } else {
    throw std::out_of_range("Invalid x or y position");
  }
}
