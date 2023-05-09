#include "View.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace {
constexpr auto f_fontPath{"assets/font.ttf"};
constexpr auto f_cellOutlineThickness{0.5};
constexpr auto f_frameSize{100};
constexpr auto f_playAreaOutlineThickness{10};
constexpr auto f_scoreVerticalOffset{30};
constexpr auto f_scoreFontSize{50};
const auto f_backgroundColor{sf::Color::White};
const auto f_playAreaColor{sf::Color::White};
const auto f_SnakeColor{sf::Color::Black};
const auto f_fruitColor{sf::Color::Black};
const auto f_scoreTextColor{sf::Color::Black};
const auto f_playAreaOutlineColor{sf::Color::Black};
}  // namespace

View::View(sf::RenderWindow &window, const Model &model)
    : m_model{model},
      m_cellSideLength{calculateCellSideLength()},
      m_window{window} {
  centreView();
}

void View::update() {
  m_window.clear();
  drawBackground();
  drawPlayArea();
  drawSnake();
  drawFruit();
  auto text{"SCORE:"};
  if (m_model.isSnakeDead()) {
    text = "GAME-OVER. TOTAL SCORE: ";
  }
  drawText(text + std::to_string(m_model.points()));
  m_window.display();
}

void View::centreView() {
  auto view{m_window.getView()};
  auto dimensions{m_model.positionLimits()};
  view.setCenter(
      calculateCellPosition({dimensions.first / 2, dimensions.second / 2}));
  m_window.setView(view);
}

void View::drawBackground() {
  auto dimensions{m_model.positionLimits()};
  sf::RectangleShape cell{
      {dimensions.first * m_cellSideLength + f_frameSize * 2,
       dimensions.second * m_cellSideLength + f_frameSize * 2}};
  cell.setFillColor(f_backgroundColor);
  m_window.draw(cell);
}

void View::drawPlayArea() {
  auto dimensions{m_model.positionLimits()};
  sf::RectangleShape cell{{m_cellSideLength * dimensions.first,
                           m_cellSideLength * dimensions.second}};
  cell.setFillColor(f_playAreaColor);
  cell.setOutlineThickness(f_playAreaOutlineThickness);
  cell.setOutlineColor(f_playAreaOutlineColor);
  cell.setPosition(f_frameSize, f_frameSize);
  m_window.draw(cell);
}

void View::drawSnake() {
  sf::RectangleShape cell{{m_cellSideLength, m_cellSideLength}};
  cell.setOutlineThickness(f_cellOutlineThickness);
  cell.setOutlineColor(f_backgroundColor);
  cell.setFillColor(f_SnakeColor);
  for (auto coord : m_model.snakePosition()) {
    cell.setPosition(calculateCellPosition(coord));
    m_window.draw(cell);
  }
}

void View::drawFruit() {
  sf::RectangleShape cell{{m_cellSideLength, m_cellSideLength}};
  cell.setFillColor(f_fruitColor);
  auto coord{m_model.fruitPosition()};
  cell.setPosition(calculateCellPosition(coord));
  m_window.draw(cell);
}

void View::drawText(const std::string &content) {
  sf::Font font;
  font.loadFromFile(f_fontPath);
  sf::Text text{content, font};
  text.setPosition(f_frameSize, f_scoreVerticalOffset);
  text.setCharacterSize(50);
  text.setFillColor(f_scoreTextColor);
  m_window.draw(text);
}

float View::calculateCellSideLength() {
  auto secreenHeight{sf::VideoMode::getDesktopMode().height};
  auto referenceLength{secreenHeight - 2 * f_frameSize};
  auto dimensions{m_model.positionLimits()};
  return static_cast<float>(referenceLength) /
         static_cast<float>(dimensions.second);
}

sf::Vector2f View::calculateCellPosition(std::pair<int, int> coord) {
  return {f_frameSize + coord.first * m_cellSideLength,
          f_frameSize + coord.second * m_cellSideLength};
}
