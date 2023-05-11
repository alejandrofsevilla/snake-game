#include "Model.hpp"

#include <algorithm>
#include <random>

namespace {
constexpr int f_pointsPerFruitEaten{5};
constexpr int f_snakeInitialLength{4};
inline int generateRandomValue(int min, int max) {
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<int> distr{min, max};
  return distr(gen);
}
}  // namespace

Model::Model(std::pair<int, int> posLimits)
    : m_positionLimits{posLimits},
      m_snake{posLimits,
              {posLimits.first / 2, posLimits.second / 2},
              Snake::Direction::Left,
              f_snakeInitialLength},
      m_fruitPosition{0, 0},
      m_points{0} {
  resetFruitPosition();
}

const std::pair<int, int> &Model::fruitPosition() const {
  return m_fruitPosition;
}

const std::vector<std::pair<int, int>> &Model::snakePosition() const {
  return m_snake.position();
}

const std::pair<int, int> &Model::positionLimits() const {
  return m_positionLimits;
}

bool Model::isSnakeDead() const { return m_snake.isDead(); }

int Model::points() const { return m_points; }

void Model::addSnakeDirectionChange(Snake::Direction dir) {
  m_snake.addDirectionChange(dir);
}

void Model::update() {
  m_snake.move();
  if (snakePosition().front() == m_fruitPosition) {
    m_points += f_pointsPerFruitEaten;
    m_snake.grow();
    resetFruitPosition();
  }
}

void Model::resetFruitPosition() {
  auto emptyPosCount{m_positionLimits.first * m_positionLimits.second -
                     snakePosition().size()};
  auto randomEmptyPosIndex{generateRandomValue(0, emptyPosCount)};
  auto index{0};
  auto &snakePos{snakePosition()};
  for (auto col = 0; col < m_positionLimits.first; col++) {
    for (auto row = 0; row < m_positionLimits.second; row++) {
      std::pair<int, int> pos{col, row};
      if (std::find(snakePos.begin(), snakePos.end(), pos) == snakePos.end()) {
        if (index == randomEmptyPosIndex) {
          m_fruitPosition = pos;
          return;
        }
        index++;
      }
    }
  }
}
