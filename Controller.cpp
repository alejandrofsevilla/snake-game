#include "Controller.hpp"

#include <SFML/Window/Event.hpp>

Controller::Controller(sf::RenderWindow &window, Model &model)
    : m_window{window}, m_model{model} {}

void Controller::update() {
  sf::Event event;
  while (m_window.pollEvent(event)) {
    switch (event.type) {
      default:
        break;
      case sf::Event::KeyPressed:
        switch (event.key.code) {
          default:
            break;
          case sf::Keyboard::Left:
            m_model.setSnakeDirection(Snake::Direction::Left);
            break;
          case sf::Keyboard::Right:
            m_model.setSnakeDirection(Snake::Direction::Right);
            break;
          case sf::Keyboard::Down:
            m_model.setSnakeDirection(Snake::Direction::Down);
            break;
          case sf::Keyboard::Up:
            m_model.setSnakeDirection(Snake::Direction::Up);
            break;
        }
    }
  }
}
