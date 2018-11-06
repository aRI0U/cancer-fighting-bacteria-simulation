#pragma once

#include "BacteriaManager.hpp"
#include "consts.hpp"

#include <math.h>
#include <iostream>

class Bacteria {

public:
  Bacteria(int x, int y);
  Bacteria(sf::Vector2f pos);
  void draw(sf::RenderTarget& target) const;
  bool update(float dt);
  sf::Vector2f get_pos();
  float get_I();
  float get_L();
  void set_I(float I);
  void set_L(float L);

private:
  sf::CircleShape shape;

  sf::Vector2f pos;
  sf::Vector2f speed;

  float I_value; // LuxI
  float L_value; // Lysis

};
