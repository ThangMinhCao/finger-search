#include "../include/Random.h"

int Random::getInt(int start, int end) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> int_dist(start, end);
  return int_dist(generator);
}

long Random::getLong(long start, long end) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> int_dist(start, end);
  return int_dist(generator);
}

std::int64_t Random::get64Int(std::int64_t start, std::int64_t end) {
  std::random_device rd;
  std::default_random_engine mt(rd());
  // std::uniform_int_distribution<long long unsigned> int_dist(0, 0xFFFFFFFFFFFFFFFF);
  std::uniform_int_distribution<std::int64_t> int_dist(start, end);
  return int_dist(mt);
}

double Random::getReal(int start, int end) {
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_real_distribution<> real_dist(start, end);
  return real_dist(generator);
}

