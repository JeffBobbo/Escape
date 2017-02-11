#include "object.h"

#include "../main.h"
#include "../gli.h"

void Object::idle()
{
}

void Object::move()
{
  // rotation
  angle += rotation * (delta / 1000.0);
  while (angle > 360.0)
    angle -= 360.0;
}

#include <iostream>
void Object::draw()
{
  // reset
  glLoadIdentity();

  // transformations
  glTranslatef(x, y, 0.0);
  glRotatef(angle, 0.0, 0.0, 1.0);
  //glScalef(width, height, 1.0f);

  // reset the colour
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  // now work out what the colour should be for the phase
  if (phase >= 0 && phase != level->phasePlayer()) // only needs to be done if we're actually in a phase
  {
    // calculate the phases colour
    double h = (2.0 * pi() / level->numPhases()) *  phase;
    RGBA c = rgba({degrees(h), 1.0, 1.0, 1.0});

    // calculate the alpha
    double t = (2.0 * pi() / level->numPhases()) * level->phasePlayer();
    double a  = std::fabs(t - h);
    a = (a > pi() ? 2.0 * pi() - a : a) / pi();

    glColor4f(c.r, c.g, c.b, a);
  }
  if (visage)
    visage->draw();
}

bool Object::aabbOverlap(const Object* const o) const
{
  return x < (o->x+o->width) &&
         x+width > o->x &&
         y < (o->y+o->height) &&
         y+height > o->y;
}

/*
bool Object::satOverlap(const Object* const o) const
{
  Vec2D axis(1.0, -1.0);

  double tProjMin = Vec2D(x, y).dot(axis);
  int tDotMin = 1;
  double tProjMax = tProjMin;
  int tDotMax = 1;

  for ()
}
*/

void Platform::move()
{
  const double p = (elapsed % period) / static_cast<double>(period);
  const double a = 2.0 * pi() * p;
  x = originx + std::cos(a) * radiusx;
  y = originy + std::sin(a) * radiusy;
}


void Door::move()
{
  if (phase == -1 || phase == level->phasePlayer())
  {
    if (distanceSquared(level->getPlayer()) < 2)
    {
      if (!open) // open the door
        open = true;
    }
    else
    {
      if (open)
        open = false;
    }
    visage = open ? vOpen : vClose;
  }
}
