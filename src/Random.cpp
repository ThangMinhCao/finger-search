#include "../include/Random.h"

int Random::getInt(int start, int end) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> int_dist(start, end);
  return int_dist(generator);
}

float Random::getReal(int start, int end) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<> real_dist(start, end);
  return real_dist(generator);
}

