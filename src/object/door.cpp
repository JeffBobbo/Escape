#include "door.h"

#include "../main.h"
#include "../visage/allvisage.h"

Door::Door(double w, double h, double u, double v, bool o, bool p)
: Object(w, h, u, v), Actuator()
{
  open = o;
  if (p)
    vOpen = VisagePolygon::rectangle(w*0.1, h);
  else
    vOpen = VisagePolygon::rectangle(w, h*0.1);
  static_cast<VisagePolygon*>(vOpen)->setColour(0xafafafFF);
  Animatrix* a = new Animatrix();
  if (p)
    a->startX = w*0.9/2.0;
  else
    a->startY = -h*0.9/2.0;
  vOpen->addAnimatrix(a);
  vClose = visage = VisagePolygon::rectangle(w, h);
  static_cast<VisagePolygon*>(vClose)->setColour(0xafafafFF);
}

Door::~Door()
{
  if (vOpen)
  {
    delete vOpen;
    vOpen = nullptr;
  }
  if (vClose)
  {
    delete vClose;
    vClose = nullptr;
  }
  visage = nullptr;
}

void Door::idle()
{
  if (isLinked())
    return;
  if (distanceSquared(level->getPlayer()) < 2)
  {
    open = true;
    visage = vOpen;
  }
  else
  {
    open = false;
    visage = vClose;
  }
}

void Door::actuate()
{
  open = trigger->on();
  visage = open ? vOpen : vClose;
}
