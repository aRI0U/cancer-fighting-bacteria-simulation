#include "Bacteria.hpp"
#include "BacteriaManager.hpp"


Bacteria::Bacteria(int x, int y) :
  shape(BACTERIA_RADIUS),
  pos(x, y),
  I_value(0),
  L_value(0)
{
  shape.setFillColor(BACTERIA_COLOR);
  shape.setOrigin(BACTERIA_RADIUS, BACTERIA_RADIUS);
  shape.setPosition(WINDOW_WIDTH / 2 + x, WINDOW_HEIGHT / 2 + y);

  speed.x = rand() % (2 * BACTERIA_MAX_SPEED + 1) - BACTERIA_MAX_SPEED;
  speed.y = rand() % (2 * BACTERIA_MAX_SPEED + 1) - BACTERIA_MAX_SPEED;
}

Bacteria::Bacteria(sf::Vector2f pos)
  : Bacteria(pos.x, pos.y) {}

void Bacteria::draw(sf::RenderTarget& target) const
{
  target.draw(shape);
}

bool Bacteria::update(float dt) {
  if (USE_BROWNIAN_MOVEMENT) {
    speed.x = rand() % (2 * BACTERIA_MAX_SPEED + 1) - BACTERIA_MAX_SPEED;
    speed.y = rand() % (2 * BACTERIA_MAX_SPEED + 1) - BACTERIA_MAX_SPEED;
  }

  pos.x += dt * speed.x;
  pos.y += dt * speed.y;
  shape.setPosition(WINDOW_WIDTH / 2 + pos.x, WINDOW_HEIGHT / 2 + pos.y);

  // update speed std::vector if bacterium reaches border of container
  if (sqrt(pos.x * pos.x + pos.y * pos.y) > CONTAINER_RADIUS - BACTERIA_RADIUS)
  {
    float normx = - pos.x / sqrt(pos.x * pos.x + pos.y * pos.y);
    float normy = - pos.y / sqrt(pos.x * pos.x + pos.y * pos.y);

    float speedx = speed.x;
    float speedy = speed.y;

    speed.x = speedx - 2 * (speedx * normx + speedy * normy) * normx;
    speed.y = speedy - 2 * (speedx * normx + speedy * normy) * normy;

    pos.x = - normx * (CONTAINER_RADIUS - BACTERIA_RADIUS);
    pos.y = - normy * (CONTAINER_RADIUS - BACTERIA_RADIUS);
  }

  // check whether bacterium self-destructs
  float L_sqr = L_value * L_value;
  float destr_prob = MAX_RATE_CELL_LYSIS * L_sqr / (CONC_HALF_MAX_LYSIS_SQUARED + L_sqr);
  if (destr_prob > 1) destr_prob = 1;
  return ((double)rand() / (double)RAND_MAX <= destr_prob);
}

sf::Vector2f Bacteria::get_pos() {
  return pos;
}
float Bacteria::get_I() { return I_value; }
float Bacteria::get_L() { return L_value; }
void Bacteria::set_I(float I) { I_value = I; }
void Bacteria::set_L(float L) { L_value = L; }
