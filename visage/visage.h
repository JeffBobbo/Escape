#ifndef VISAGE_H_INCLUDE
#define VISAGE_H_INCLUDE

#include <vector>

#include "animatrix.h"


class Visage
{
public:
  enum class Type
  {
    POLYGON = 0,
    COMPLEX
  };

  Visage() {}
  virtual ~Visage()
  {
    for (Animatrix* a : animatrices)
      delete a;
  }

  virtual inline Type type() const = 0;

  virtual void draw() = 0;
  virtual void addAnimatrix(Animatrix* const a) { animatrices.push_back(a); }

protected:
  std::vector<Animatrix* > animatrices;
};

#endif
