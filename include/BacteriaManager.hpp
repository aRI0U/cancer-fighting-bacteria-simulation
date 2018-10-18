#pragma once

#include "Bacteria.hpp"
#include "consts.hpp"


class Bacteria;

class BacteriaManager {
public:
  BacteriaManager();
  void new_bacteria(sf::Vector2f pos);
  void update(float dt);
  void drawBacteria(sf::RenderTarget &target);

private:
  std::vector<Bacteria> bacteria;
};
