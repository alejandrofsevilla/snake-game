#ifndef SNAKE_GAME_SNAKE_HPP
#define SNAKE_GAME_SNAKE_HPP

#include <queue>
#include <vector>

class Snake {
 public:
  enum class Direction { Up, Down, Left, Right };

  Snake(std::pair<int, int> posLimits, std::pair<int, int> headPos0,
        Direction dir0, int len0);

  const std::vector<std::pair<int, int>> &position() const;
  bool isDead() const;

  void move();
  void grow();
  void addDirectionChange(Direction dir);

 private:
  void moveHead();
  void moveBody();
  void updateDirection();
  void updateIsDead();

  const std::pair<int, int> m_positionLimits;
  std::vector<std::pair<int, int>> m_position;
  std::queue<Direction> m_directionChanges;
  Direction m_direction;
  int m_length;
  bool m_isDead;
};

#endif
