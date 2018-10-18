
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
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Replicating Bacteria to Destroy Cancer Cells");

  constexpr float MAX_FPS = 60;
  const float time_between_frames = 1.0 / MAX_FPS;

  sf::Clock clock;

  BacteriaManager b;
  b.new_bacteria(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (clock.getElapsedTime().asSeconds() >= time_between_frames) {
      window.clear(WINDOW_BACKGROUND_COLOR);
      sf::Time elapsed = clock.restart();

      b.update(elapsed.asSeconds());
      b.drawBacteria(window);

      window.display();
    }
  }

  return 0;
}
