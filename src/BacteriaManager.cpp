#include "Bacteria.hpp"
#include "BacteriaManager.hpp"



BacteriaManager::BacteriaManager():
  bacteria()
{}

void BacteriaManager::new_bacteria(sf::Vector2f pos) {
  Bacteria b(pos, this);
  bacteria.push_back(b);
}

void BacteriaManager::update(float dt) {
  for (auto &b: bacteria)
    b.update(dt);

  if (bacteria.size() > 2000) {
    bacteria.erase(bacteria.begin(), bacteria.begin()+1750);
  }
}

void BacteriaManager::drawBacteria(sf::RenderTarget &target) {
  for (auto &b: bacteria)
    b.draw(target);
}
