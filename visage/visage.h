#ifndef VISAGE_H_INCLUDE
#define VISAGE_H_INCLUDE

#include <vector>

#include "animatrix.h"


class Visage
{
public:
  Visage() {}
  virtual ~Visage()
  {
    for (Animatrix* a : animatrices)
      delete a;
  }

  virtual void draw() = 0;
  virtual void addAnimatrix(Animatrix* const a) { animatrices.push_back(a); }

protected:
  std::vector<Animatrix* > animatrices;
};

#endif
