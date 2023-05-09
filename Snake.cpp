#include "Snake.hpp"

#include <algorithm>

namespace {
inline constexpr std::pair<int, int> directionVector(Snake::Direction dir) {
  switch (dir) {
    case Snake::Direction::Up:
      return {0, -1};
    case Snake::Direction::Down:
      return {0, 1};
    case Snake::Direction::Left:
      return {-1, 0};
    case Snake::Direction::Right:
      return {1, 0};
    default:
      return {};
  }
}

inline std::vector<std::pair<int, int>> calculateInitialPosition(
    std::pair<int, int> headPos, Snake::Direction dir, int len) {
  std::vector<std::pair<int, int>> position{headPos};
  for (auto i = 1; i < len; i++) {
    auto pos{position[i - 1]};
    pos.first -= directionVector(dir).first;
    pos.second -= directionVector(dir).second;
    position.push_back(pos);
  }
  return position;
}
}  // namespace

Snake::Snake(std::pair<int, int> posLimits, std::pair<int, int> headPos0,
             Direction dir0, int len0)
    : m_positionLimits{posLimits},
      m_position{calculateInitialPosition(headPos0, dir0, len0)},
      m_directionChanges{},
      m_direction{dir0},
      m_length{len0},
      m_isDead{false} {};

const std::vector<std::pair<int, int>> &Snake::position() const {
  return m_position;
}

bool Snake::isDead() const { return m_isDead; }

void Snake::move() {
  if (m_isDead) {
    return;
  }
  updateDirection();
  moveBody();
  moveHead();
  updateIsDead();
}

void Snake::grow() { m_position.push_back({m_position.back()}); };

void Snake::addDirectionChange(Direction dir) { m_directionChanges.push(dir); }

void Snake::moveHead() {
  auto &head = m_position.front();
  head.first += directionVector(m_direction).first;
  head.second += directionVector(m_direction).second;
  if (head.first < 0) {
    head.first = m_positionLimits.first - 1;
  } else if (head.first >= m_positionLimits.first) {
    head.first = 0;
  }
  if (head.second < 0) {
    head.second = m_positionLimits.second - 1;
  } else if (head.second >= m_positionLimits.second) {
    head.second = 0;
  }
}

void Snake::moveBody() {
  for (auto it = m_position.rbegin(); it != m_position.rend() - 1; it++) {
    *it = *(it + 1);
  }
};

void Snake::updateDirection() {
  if (m_directionChanges.empty()) {
    return;
  }
  auto dir{m_directionChanges.front()};
  auto move{directionVector(dir)};
  auto currentMove{directionVector(m_direction)};
  if (move.first * currentMove.first >= 0 &&
      move.second * currentMove.second >= 0) {
    m_direction = dir;
  }
  m_directionChanges.pop();
}

void Snake::updateIsDead() {
  if (std::find(m_position.begin() + 1, m_position.end(), m_position.front()) !=
      m_position.end()) {
    m_isDead = true;
  }
}
