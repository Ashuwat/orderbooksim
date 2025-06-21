#include "../include/simulationContext.h"
#include <random>

SimulationContext::SimulationContext() {
    std::mt19937_64 rng {};
    std::normal_distribution<float> norm_dist {};
    std::bernoulli_distribution coin_flip {};
    std::uniform_int_distribution<int> uniform_dist {};
}