#ifndef ANIMATRIX_H_INCLUDE
#define ANIMATRIX_H_INCLUDE

#include <stdint.h>

class Animatrix
{
public:
  Animatrix() {}
  virtual ~Animatrix() {}

  inline bool isVisible() const { return visible; }

private:
  uint32_t start, stop, loop, offset;
  uint32_t startColour, endColour;
  double startSize, endSize;
  double startAngle, endAngle, rotation;
  double startX, startY, endX, endY;
  bool visible;
};

#endif
