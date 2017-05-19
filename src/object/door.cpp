#include "door.h"

#include "../main.h"
#include "../visage/allvisage.h"

Door::Door(Vec2D sz, Vec2D pos, bool o, bool p)
: Object(sz, pos), Actuator()
{
  open = o;
  if (p)
    vOpen = VisagePolygon::rectangle(sz.x*0.1, sz.y);
  else
    vOpen = VisagePolygon::rectangle(sz.x, sz.y*0.1);
  static_cast<VisagePolygon*>(vOpen)->setColour(0xafafafFF);
  Animatrix* a = new Animatrix();
  if (p)
    a->startX = sz.x*0.9/2.0;
  else
    a->startY = -sz.y*0.9/2.0;
  vOpen->addAnimatrix(a);
  vClose = visage = VisagePolygon::rectangle(sz.x, sz.y);
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

void Door::setVisageOpen(Visage* const v)
{
  delete vOpen;
  vOpen = v;
  if (open)
    visage = vOpen;
}

void Door::setVisageClose(Visage* const v)
{
  delete vClose;
  vClose = v;
  if (!open)
    visage = vClose;
}