#include "util.h"

#include <iostream>

std::mt19937 mt;

void seed(uint64_t s)
{
  #ifndef NDEBUG
  std::cout << "Seed: " << s << std::endl;
  #endif
  std::seed_seq sq = {s >> 32, s & 0xFFFFFFFF};
  mt.seed(sq);
}

std::mt19937& getMT()
{
  return mt;
}