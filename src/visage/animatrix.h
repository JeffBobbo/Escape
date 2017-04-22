#ifndef ANIMATRIX_H_INCLUDE
#define ANIMATRIX_H_INCLUDE

#include <stdint.h>

#include "../util.h"
#include "../colour.h"

class Animatrix
{
public:
  Animatrix();
  virtual ~Animatrix() {}

  inline bool isActive() const
  {
    if (loop == 0) // non-looping animatrices are always active
      return true;
    millis_t progress = tickCount() % loop;
    return progress >= start && progress < end;
  }
  inline bool isVisible() const { return visible; }

  void apply() const;


  millis_t start, end, loop;
  RGBA_t startColour, endColour;
  double startScaleX, startScaleY, endScaleX, endScaleY;
  double startAngle, endAngle, rotation;
  double startX, startY, endX, endY;
  bool visible;
private:
  mutable double curAngle;
};

#endif
