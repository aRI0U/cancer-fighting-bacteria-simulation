
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Bacteria.hpp"
#include "BacteriaManager.hpp"
#include "consts.hpp"



int main() {
  srand(time(NULL));

  sf::ContextSettings settings;
  settings.antialiasingLevel = 32;
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Replicating Bacteria to Destroy Cancer Cells");

  sf::Clock clock;

  BacteriaManager b;
  for (int i = 0; i < 100; i++)
    b.new_bacteria(sf::Vector2f(0, 0)); // (0,0) is center of window

  sf::CircleShape container(CONTAINER_RADIUS, 10000);
  container.setOrigin(CONTAINER_RADIUS, CONTAINER_RADIUS);
  container.setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
  container.setFillColor(CONTAINER_COLOR);
  container.setOutlineColor(CONTAINER_BORDER_COLOR);
  container.setOutlineThickness(2);

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (clock.getElapsedTime().asSeconds() >= DT) {
      std::cout << 1.0 / clock.getElapsedTime().asSeconds() << " FPS (limit: " << 1.0 / DT << ")\n";
      window.clear(WINDOW_BACKGROUND_COLOR);
      window.draw(container);
      clock.restart();

      b.update(DT);
      b.drawAHL(window);
      b.drawBacteria(window);

      window.display();
    }
  }

  return 0;
}
