#pragma once

#include <SFML/Graphics.hpp>

#include "Bacteria.hpp"
#include "consts.hpp"

#include <algorithm>

class Bacteria;

class BacteriaManager {
public:
  BacteriaManager();
  void new_bacteria(sf::Vector2f pos);
  void update(float dt);
  void drawBacteria(sf::RenderTarget &target);
  void drawAHL(sf::RenderTarget &target);
  
private:
  std::vector<Bacteria> bacteria;
  std::vector<std::vector<float>> AHL;
};
