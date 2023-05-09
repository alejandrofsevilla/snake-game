#include <SFML/Graphics/RenderWindow.hpp>

#include "Controller.hpp"
#include "Model.hpp"
#include "View.hpp"

namespace {
constexpr auto f_antialasingLevel{4};
constexpr auto f_frameRateLimit{10};
constexpr std::pair<int, int> f_dimensions{40, 40};

inline void init(sf::RenderWindow &window) {
  sf::ContextSettings settings;
  settings.antialiasingLevel = f_antialasingLevel;
  window.create(sf::VideoMode::getDesktopMode(), "Snake", sf::Style::Default,
                settings);
  window.setFramerateLimit(f_frameRateLimit);
  window.setVerticalSyncEnabled(true);
}
}  // namespace

int main() {
  sf::RenderWindow window;
  init(window);
  Model model{f_dimensions};
  Controller controller{window, model};
  View view{window, model};
  while (window.isOpen()) {
    controller.update();
    view.update();
    model.update();
  }
  return 0;
}
