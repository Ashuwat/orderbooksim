#include "../include/simulationContext.h"
#include <random>
#include <iostream>

SimulationContext::SimulationContext(int seed) : 
      rng(seed),
      norm_dist(0.0f, 1.0f),
      coin_flip(0.5),
      uniform_dist(0, 100) {}