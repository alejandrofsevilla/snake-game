#ifndef SNAKE_GAME_MODEL_HPP
#define SNAKE_GAME_MODEL_HPP

#include "Snake.hpp"

class Model {
 public:
  Model(std::pair<int, int> posLimits);

  const std::pair<int, int> &fruitPosition() const;
  const std::vector<std::pair<int, int>> &snakePosition() const;
  const std::pair<int, int> &positionLimits() const;

  bool isSnakeDead() const;
  int points() const;

  void setSnakeDirection(Snake::Direction dir);
  void update();

 private:
  void resetFruitPosition();

  const std::pair<int, int> m_positionLimits;
  Snake m_snake;
  std::pair<int, int> m_fruitPosition;
  int m_points;
};

#endif
