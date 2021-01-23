#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H 
#include <random>
#include "boost/random.hpp"

class Random{
  public:
    static int getInt(int start, int end);
    static float getReal(int start, int end);
};
#endif