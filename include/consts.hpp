#pragma once

#include <SFML/Graphics.hpp>

const float _FACTOR = .5;

// graphics

const int WINDOW_WIDTH = 1600.0 * _FACTOR;
const int WINDOW_HEIGHT = 1600.0 * _FACTOR;
const sf::Color WINDOW_BACKGROUND_COLOR = sf::Color(210,210,210);

const int CONTAINER_RADIUS = 700.0 * _FACTOR;
const sf::Color CONTAINER_BORDER_COLOR = sf::Color(150,150,150);
const sf::Color CONTAINER_COLOR = sf::Color(200,200,200);

const int BACTERIA_RADIUS = 10.0 * _FACTOR;
const sf::Color BACTERIA_COLOR = sf::Color(100, 100, 200, 200);


// simulation

const bool USE_BROWNIAN_MOVEMENT = true;

const float DT = 0.1; // sec
const int BACTERIA_MAX_SPEED = 120.0 * _FACTOR; // px/sec

const float SPLIT_PROBABILITY = 0.02; // mu_G

const float MAX_RATE_CELL_LYSIS = 10; // k
const float CONC_HALF_MAX_LYSIS_SQUARED = 2 * 2; // L0^2
const float AHL_PROD_RATE = 25;
const float LUX_PROM_BASAL_PROD = 0.5;
const float LUX_PROM_AHL_INDUCED_PROD = 35;
const float AHL_BINDING_AFFINITY_TO_LUX = 5;
const float LYSIS_COPY_NUMBER = 0.5; // CL
const float LUXI_COPY_NUMBER = 1; // CI
const float BASAL_DEGRADATION_LYSIS = 2; // γL
const float BASAL_DEGRADATION_LUXI = 2; // γI


/*
μG (Dilution due to cell growth) 0.2;
N0 (Maximum cell population size) 10;
k (Maximum rate of cell lysis) 10;
L0 (Conc. of lysis gene resulting in half maximum lysis) 2;
n (Hill coefficient of lysis function) 2;
b (AHL production rate) 25;
μ (Maximum AHL clearance rate due to flow) 12;
CL (Lysis gene copy number) 0.5;
CI (LuxI copy number) 1 ;
α0 (Lux promoter basal production) 0.5;
αH (Lux promoter AHL induced production) 35;
H0 (AHL binding affinity to Lux promoter) 5;
γL (Basal degradation of lysis protein) 2;
γI (Basal degradation of LuxI) 2;
γC (ClpXP degradation of LuxI) 12.
*/
