#include "Slither/Controller.hpp"

using namespace Slither;

Controller::Controller(Board board)
    : m_board(std::move(board)),
      m_state(State::RUNNING),
      m_score(0) {
  auto found_head = false;
  for(auto y = 0; y < m_board.get_height() && !found_head; ++y) {
    for(auto x = 0; x < m_board.get_width() && !found_head; ++x) {
      if(m_board.get(x, y) == Board::Cell::HEAD) {
        m_snake_positions.push_front({x, y});
        found_head = true;
      }
    }
  }
  if(!found_head) {
    m_state = State::GAME_OVER;
    return;
  }
  auto is_body = [&] (int x, int y) {
    return x >= 0 && x < m_board.get_width() && y >= 0 &&
      y < m_board.get_height() &&
      (m_board.get(x, y) == Board::Cell::BODY ||
        m_board.get(x, y) == Board::Cell::TAIL);
  };
  auto x = m_snake_positions.front().first;
  auto y = m_snake_positions.front().second;
  while(true) {
    auto found_body = false;
    if(is_body(x - 1, y)) {
      x -= 1;
      found_body = true;
    } else if(is_body(x + 1, y)) {
      x += 1;
      found_body = true;
    } else if(is_body(x, y - 1)) {
      y -= 1;
      found_body = true;
    } else if(is_body(x, y + 1)) {
      y += 1;
      found_body = true;
    }
    if(found_body) {
      m_snake_positions.push_back({x, y});
      if(m_board.get(x, y) == Board::Cell::TAIL) {
        break;
      }
    } else {
      break;
    }
  }
}

const Board& Controller::get_board() const {
  return m_board;
}

Controller::State Controller::get_state() const {
  return m_state;
}

Controller::State Controller::update(Direction direction) {
  if(m_state == State::GAME_OVER) {
    return m_state;
  }
  auto head_x = m_snake_positions.front().first;
  auto head_y = m_snake_positions.front().second;
  auto new_head_x = head_x;
  auto new_head_y = head_y;
  switch(direction) {
    case Direction::UP:
      --new_head_y;
      break;
    case Direction::DOWN:
      ++new_head_y;
      break;
    case Direction::LEFT:
      --new_head_x;
      break;
    case Direction::RIGHT:
      ++new_head_x;
      break;
  }
  if(new_head_x < 0 || new_head_x >= m_board.get_width() ||
      new_head_y < 0 || new_head_y >= m_board.get_height()) {
    m_state = State::GAME_OVER;
    return m_state;
  }
  auto cell = m_board.get(new_head_x, new_head_y);
  if(cell == Board::Cell::BODY || cell == Board::Cell::TAIL) {
    m_state = State::GAME_OVER;
    return m_state;
  }
  auto ate_apple = cell == Board::Cell::APPLE;
  m_board.set(new_head_x, new_head_y, Board::Cell::HEAD);
  auto body_cell = [&] {
    if(m_snake_positions.size() > 1) {
      return Board::Cell::BODY;
    }
    return Board::Cell::TAIL;
  }();
  m_board.set(head_x, head_y, body_cell);
  m_snake_positions.push_front({new_head_x, new_head_y});
  if(ate_apple) {
    m_score += 1;
  } else {
    auto tail = m_snake_positions.back();
    m_snake_positions.pop_back();
    m_board.set(tail.first, tail.second, Board::Cell::EMPTY);
    if(!m_snake_positions.empty()) {
      auto new_tail = m_snake_positions.back();
      m_board.set(new_tail.first, new_tail.second, Board::Cell::TAIL);
    }
  }
  return m_state;
}

int Controller::get_score() const {
  return m_score;
}
