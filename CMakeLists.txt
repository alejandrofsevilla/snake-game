cmake_minimum_required(VERSION 3.22.0)

project(snake-game LANGUAGES CXX)

add_executable(snake-game
  Snake.hpp
  Snake.cpp
  Model.hpp
  Model.cpp
  Controller.hpp
  Controller.cpp
  View.hpp
  View.cpp
  Main.cpp
  )

target_compile_features(snake-game PRIVATE cxx_std_17)

target_compile_options(snake-game PRIVATE -Wall -Wextra -Wpedantic -Werror -O0)

target_link_libraries(snake-game PRIVATE
 sfml-graphics
 sfml-window
 sfml-system
)

