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
  glScalef(width, height, 1.0f);

  // reset the colour
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

  // now work out what the colour should be for the phase
  if (phase >= 0) // only needs to be done if we're actually in a phase
  {
    int16_t pphase = level->phasePlayer();
    double phaseOffset = (((pphase - phase) + level->numPhases()) % level->numPhases()) / static_cast<double>(level->numPhases());
    if (phaseOffset < 0.5)
      glColor4f(1.0 - phaseOffset, 0.5, 0.5, 0.75);
    else
      glColor4f(0.5, 0.5, 0.5 + phaseOffset, 0.75);
  }
  if (visage)
    visage->draw();
}

#include <iostream>
void Platform::move()
{
  const double p = (elapsed % period) / static_cast<double>(period);
  const double a = 2.0 * pi() * p;
  x = originx + std::cos(a) * radiusx;
  y = originy + std::sin(a) * radiusy;
}
