#ifndef PLATFORM_H_INCLUDE
#define PLATFORM_H_INCLUDE

#include "object.h"
#include "../types.h"
#include "../util.h"

class Platform : public Object
{
public:
  Platform(double w, double h, double u, double v, double rx = 0.0, double ry = 0.0, millis_t p = 0);
  virtual ~Platform() {}

  virtual inline Type type() const { return Type::PLATFORM; }
  virtual inline bool isSolid() const { return true; }
  virtual void move();

  inline bool stationary() const { return !period || (radiusx == 0.0 && radiusy == 0.0); }
  void drawPath();

private:
  double radiusx;
  double radiusy;
  millis_t period;
  Vec2D origin;
};

#endif
