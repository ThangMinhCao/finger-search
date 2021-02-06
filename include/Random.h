#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H 

#include <random>
class Random{
  public:
    static int getInt(int start, int end);
    static long getLong(long start, long end);
    static std::int64_t get64Int(std::int64_t start, std::int64_t end);
    static double getReal(int start, int end);
};
#endif // RANDOM_GEN_H