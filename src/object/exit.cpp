#include "exit.h"

#include "../visage/polygon.h"

Exit::Exit(Vec2D pos, const std::string& n)
  : Object({0.5, 0.5}, std::move(pos))
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
