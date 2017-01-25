#ifndef VISAGE_H_INCLUDE
#define VISAGE_H_INCLUDE

#include <vector>

#include "animatrix.h"


class Visage
{
public:
  Visage() {}
  virtual ~Visage() {}

  virtual void draw() = 0;

private:
  std::vector<Animatrix* > animatrices;
};

#endif
