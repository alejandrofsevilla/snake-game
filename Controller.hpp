#ifndef SNAKE_GAME_CONTROLLER_HPP
#define SNAKE_GAME_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include "Model.hpp"

namespace sf {
class Event;
}

class Controller {
 public:
  Controller(sf::RenderWindow &window, Model &model);

  void update();

 private:
  sf::RenderWindow &m_window;
  Model &m_model;
};

#endif
