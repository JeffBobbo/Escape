#include "object.h"

#include "../main.h"
#include "../gli.h"
#include "../visage/allvisage.h"

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
  glPushMatrix();

  // transformations
  glTranslated(x, y, 0.0);
  glRotated(angle, 0.0, 0.0, 1.0);

  // reset the colour
  glColor4d(1.0, 1.0, 1.0, 1.0);

  // now work out what the colour should be for the phase
  if (phase >= 0 && phase != level->phasePlayer()) // only needs to be done if we're actually in a phase
  {
    // calculate the phases colour
    double h = (360.0 / level->numPhases()) *  phase;
    RGBA c = rgba({h, 1.0, 1.0, 1.0});

    // calculate the alpha
    double t = (2.0 * pi() / level->numPhases()) * level->phasePlayer();
    double a  = std::fabs(t - h);
    a = (a > pi() ? 2.0 * pi() - a : a) / pi();

    glColor4d(c.r, c.g, c.b, a);
  }
  if (visage)
    visage->draw();

  glPopMatrix();
}

bool Object::aabbOverlap(const Object* const o) const
{
  return x-width/2.0 < o->x+o->width/2.0 &&
         x+width/2.0 > o->x-o->width/2.0 &&
         y-height/2.0 < o->y+o->height/2.0 &&
         y+height/2.0 > o->y-o->height/2.0;
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
  const double p = static_cast<double>(elapsed % period) / static_cast<double>(period);
  const double a = 2.0 * pi() * p;
  x = originx + std::cos(a) * radiusx;
  y = originy + std::sin(a) * radiusy;
}


Door::Door(double w, double h, double u, double v, bool o, bool p)
: Wall(w, h, u, v)
{
  trigger = nullptr;
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
    a->startY = h*0.9/2.0;
  vOpen->addAnimatrix(a);
  vClose = visage;
  static_cast<VisagePolygon*>(vClose)->setColour(0xafafafFF);
}

void Door::idle()
{
  if (trigger)
  {
    open = trigger->on();
  }
  else
  {
    if ((phase == -1 || phase == level->phasePlayer()) &&
        distanceSquared(level->getPlayer()) < 2)
      open = true;
    else
      open = false;
  }
  visage = open ? vOpen : vClose;
}

Button::Button(double u, double v, millis_t t)
  : Object(0.25, 0.25, u, v)
  , last(0), timeout(t)
{
  visage = VisagePolygon::circle(0.1, 16);
  static_cast<VisagePolygon*>(visage)->setColour(0xff7f7fff);
}

void Button::idle()
{
  if (on())
    static_cast<VisagePolygon*>(visage)->setColour(0xff0000ff);
  else
    static_cast<VisagePolygon*>(visage)->setColour(0xff7f7fff);
}

Exit::Exit(double u, double v, const std::string& n)
  : Object(1.0, 1.0, u, v)
  , name(n)
{
  visage = VisagePolygon::triangle(1.0, 1.0, 0.0);
  static_cast<VisagePolygon*>(visage)->setColour(0xFFFF00FF);
}

Grid::Grid(double w, double h, double u, double v, phase_t p)
  : Object(w, h, u, v)
  , target(p)
{
  visage = new VisageComplex();
  {
    //VisagePolygon* bg = VisagePolygon::rectangle(w, h);
    VisageTexture* bg = new VisageTexture(w, h, "img/background/tile2.png", -0.5, -0.5);
    static_cast<VisageTexture*>(bg)->setRepeat(w, h);
    Animatrix* a0 = new Animatrix();
    a0->startColour = 0xFFFFFF7F;
    a0->endColour   = 0xFFFFFF3F;
    a0->start =    0;
    a0->end   = 1000;
    a0->loop  = 2000;
    bg->addAnimatrix(a0);
    Animatrix* a1 = new Animatrix();
    a1->startColour = 0xFFFFFF3F;
    a1->endColour   = 0xFFFFFF7F;
    a1->start = 1000;
    a1->end   = 2000;
    a1->loop  = 2000;
    bg->addAnimatrix(a1);
    static_cast<VisageComplex*>(visage)->add(bg);
  }
  {
    ParticleSystem* ps = new ParticleSystem(1000, 25);
    ps->setParticleImage("img/particle_soft.png");
    ps->setColours(fromInt(0xFFFFFFFF), fromInt(0xFFFFFF00));
    ps->lifeMin = 1000;
    ps->lifeMax = 1500;
    ps->sizeStart = 1.0f / 8.0f;
    ps->sizeEnd   = 1.0f / 32.0f;
    ps->speedStart = 0.1;
    ps->speedEnd = 0.0;
    ps->offsetX = w;
    ps->offsetY = h;
    ps->rectangle = true;
    //ps->setGravity(true);
    static_cast<VisageComplex*>(visage)->add(ps);
  }
}

void Grid::idle()
{
  if (level->phasePlayer() != target)
  {
    if (aabbOverlap(level->getPlayer()))
      level->getPlayer()->phase = target;
  }
}
