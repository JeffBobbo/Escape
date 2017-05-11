#include "exit.h"

#include "../visage/polygon.h"

Exit::Exit(double u, double v, const std::string& n)
  : Object(0.5, 0.5, u, v)
  , name(n)
{
  visage = VisagePolygon::triangle(0.5, 0.5, 0.0);
  static_cast<VisagePolygon*>(visage)->setColour(0xFFFF00FF);
}

bool Exit::active() const
{
  if (trigger)
    return trigger->on();
  return true;
}
