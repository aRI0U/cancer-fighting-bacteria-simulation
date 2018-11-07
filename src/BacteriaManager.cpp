#include "Bacteria.hpp"
#include "BacteriaManager.hpp"



BacteriaManager::BacteriaManager():
  bacteria(),
  AHL(WINDOW_HEIGHT, std::vector<float>(WINDOW_WIDTH, 0))
{}

void BacteriaManager::new_bacteria(sf::Vector2f pos) {
  Bacteria b(pos);
  bacteria.push_back(b);
}

void BacteriaManager::update(float dt) {
  int nb_split = 0;
  int nb_death = 0;

  std::vector<std::vector<float>> AHL_tmp = AHL;
  for (int i = 1; i < WINDOW_HEIGHT - 1; i++)
    for (int j = 1; j < WINDOW_WIDTH - 1; j++) {
      AHL[i][j] = 0;
      for (int di = -1; di <= 1; di++)
        for (int dj = -1; dj <= 1; dj++)
          AHL[i][j] += AHL_tmp[i+di][j+dj];
      AHL[i][j] /= 9;
    }

  std::vector<Bacteria> new_bacteria;

  for (auto &b: bacteria) {
    bool destruct = b.update(dt);
    if (!destruct) {
      AHL[(int)b.get_pos().y + WINDOW_HEIGHT/2][(int)b.get_pos().x + WINDOW_WIDTH/2] += AHL_PROD_RATE * b.get_I();

      float total_ahl = 0;
      for (int i = -30; i <= 30; i++)
        for (int j = -30; j <= 30; j++)
          total_ahl += AHL[(int)b.get_pos().y + WINDOW_HEIGHT/2 + i][(int)b.get_pos().x + WINDOW_WIDTH/2 + j];

      float tmp = total_ahl / AHL_BINDING_AFFINITY_TO_LUX;
      tmp = pow(tmp, 4);
      float activation = LUX_PROM_BASAL_PROD + LUX_PROM_AHL_INDUCED_PROD * tmp / (1 + tmp);

      float DT_test = 1e-4;
      b.set_I(DT_test * (LUXI_COPY_NUMBER * activation - BASAL_DEGRADATION_LUXI * b.get_I()) + b.get_I());
      b.set_L(DT_test * (LYSIS_COPY_NUMBER * activation - BASAL_DEGRADATION_LYSIS * b.get_L()) + b.get_L());

      if ((double)rand() / (double)RAND_MAX <= SPLIT_PROBABILITY) {
        b.set_I(b.get_I() / 2);
        b.set_L(b.get_L() / 2);
        new_bacteria.push_back(b);
        new_bacteria.push_back(b);
        nb_split++;
      }
      else
        new_bacteria.push_back(b);
    }
    else
      nb_death++;
  }

  bacteria = new_bacteria;
  std::cout << bacteria.size() << " bacteria | " << nb_split << " splits | " << nb_death << " deaths\n";
}

void BacteriaManager::drawBacteria(sf::RenderTarget &target) {
  for (auto &b: bacteria)
    b.draw(target);
}

void BacteriaManager::drawAHL(sf::RenderTarget &target) {
  std::vector<sf::Vertex> points;
  for (int i = 0; i < WINDOW_HEIGHT; i++)
    for (int j = 0; j < WINDOW_WIDTH; j++) {
      int i2 = i - WINDOW_HEIGHT/2, j2 = j - WINDOW_WIDTH/2;
      if (AHL[i][j] > 0 && sqrt((float)(i2*i2 + j2*j2)) < CONTAINER_RADIUS) {
        float x = AHL[i][j];// * 200.0 / 500.0;
        if (x * 30 > 200) x = 200/30;
        sf::Color ahl_color(50 + x*30, 50, 50, 100);
        // sf::Color ahl_color(200, 200 - x, 200 - x, 200);
        sf::Vertex v(sf::Vector2f(j, i), ahl_color);
        points.push_back(v);
      }
    }

  target.draw(&points[0], points.size(), sf::Points);
}
