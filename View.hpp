#ifndef SNAKE_GAME_VIEW_HPP
#define SNAKE_GAME_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "Model.hpp"

class View {
 public:
  View(sf::RenderWindow &window, const Model &model);
  void update();

 private:
  void centreView();
  void drawBackground();
  void drawPlayArea();
  void drawSnake();
  void drawFruit();
  void drawText(const std::string &content);

  float calculateCellSideLength();
  sf::Vector2f calculateCellPosition(std::pair<int, int> coord);

  const Model &m_model;
  const sf::Vector2f m_playAreaDimensions;
  const float m_cellSideLength;
  sf::RenderWindow &m_window;
};

#endif
