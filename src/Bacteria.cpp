#include "Bacteria.hpp"
#include "BacteriaManager.hpp"


Bacteria::Bacteria(int x, int y, BacteriaManager *manager) :
  shape(BACTERIA_RADIUS),
  pos(x, y),
  manager(manager),
  time_since_split(0),
  split_delay(1 * ((double) rand() / (RAND_MAX)) + 1)
{
  shape.setFillColor(BACTERIA_COLOR);
  shape.setOrigin(BACTERIA_RADIUS, BACTERIA_RADIUS);
  shape.setPosition(x, y);

  speed.x = rand() % (2 * BACTERIA_MAX_SPEED + 1) - BACTERIA_MAX_SPEED;
  speed.y = rand() % (2 * BACTERIA_MAX_SPEED + 1) - BACTERIA_MAX_SPEED;
}
Bacteria::Bacteria(sf::Vector2f pos, BacteriaManager *manager)
  : Bacteria(pos.x, pos.y, manager) {}

void Bacteria::draw(sf::RenderTarget& target) const
{
  target.draw(shape);
}

void Bacteria::update(float dt) {
  speed.x = rand() % (2 * BACTERIA_MAX_SPEED + 1) - BACTERIA_MAX_SPEED;
  speed.y = rand() % (2 * BACTERIA_MAX_SPEED + 1) - BACTERIA_MAX_SPEED;

  pos.x += dt * speed.x;
  pos.y += dt * speed.y;

  shape.setPosition(pos.x, pos.y);

  time_since_split += dt;
  if (time_since_split > split_delay) {
    time_since_split = 0;
    split();
  }
}

void Bacteria::split() {
  manager->new_bacteria(pos);
}
