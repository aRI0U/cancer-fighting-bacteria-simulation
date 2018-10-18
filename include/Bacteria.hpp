#pragma once

#include "BacteriaManager.hpp"
#include "consts.hpp"


class Bacteria {
public:
  Bacteria(int x, int y, BacteriaManager *manager);
  Bacteria(sf::Vector2f pos, BacteriaManager *manager);
  void draw(sf::RenderTarget& target) const;
  void update(float dt);
  void split();

private:
  sf::CircleShape shape;

  sf::Vector2f pos;
  sf::Vector2f speed;

  BacteriaManager *manager;

  float time_since_split;
  float split_delay;
};
