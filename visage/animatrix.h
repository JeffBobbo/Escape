#ifndef ANIMATRIX_H_INCLUDE
#define ANIMATRIX_H_INCLUDE

#include <stdint.h>

#include "../util.h"
#include "../colour.h"

class Animatrix
{
public:
  Animatrix()
  {
    start = end = loop = offset = 0;
    startColour = endColour = 0xFFFFFFFF;
    startSize = endSize = 1.0;
    startAngle = endAngle = rotation = 0.0;
    startX = startY = endX = endY = 0.0;
    visible = true;
  }
  virtual ~Animatrix() {}

  inline bool isActive() const
  {
    if (loop == 0) // non-looping animatrices are always active
      return true;
    uint32_t progress = tickCount() % loop;
    return progress > start && progress < end;
  }
  inline bool isVisible() const { return visible; }

  uint64_t start, end, loop, offset;
  double startSize, endSize;
  RGBA_t startColour, endColour;
  double startAngle, endAngle, rotation;
  double startX, startY, endX, endY;
  bool visible;
private:
};

#endif
