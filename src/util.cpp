#include "util.h"

#include <iostream>

std::mt19937 mt;

void seed(uint64_t s)
{
  #ifndef NDEBUG
  std::cout << "Seed: " << s << std::endl;
  #endif
  mt.seed(s);
}

std::mt19937& getMT()
{
  return mt;
}