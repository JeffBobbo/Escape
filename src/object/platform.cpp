#include "platform.h"

#include <string>

#include "../visage/allvisage.h"
#include "../gli.h"

Platform::Platform(double w, double h, double u, double v, double rx, double ry, millis_t p)
  : Object(w, h, u, v)
  , radiusx(rx), radiusy(ry)
  , period(p)
  , origin(u, v)
{
  //visage = VisagePolygon::rectangle(w, h);
  //static_cast<VisagePolygon*>(visage)->setColour(0x7f7f7fFF);
  if (p == 0)
  {
    visage = new VisageTexture(w, h, "img/background/tile1.png");
    static_cast<VisageTexture*>(visage)->setRepeat(w, h);
  }
  else
  {
    visage = new VisageComplex();
    {
      VisageTexture* vt = new VisageTexture(w, h, "img/platforms.png");
      vt->setAtlasSprite("platform2");
      static_cast<VisageComplex*>(visage)->add(vt);
    }
    {
      ParticleSystem* ps = new ParticleSystem(200, 100);
      ps->setParticleImage("img/particle_soft.png");
      ps->setColours(fromInt(0x003AD9FF), fromInt(0x90C3D400));
      ps->lifeMin = 500;
      ps->lifeMax = 875;
      ps->sizeStart = 0.25;
      ps->sizeEnd = 0.0625;
      ps->speedStart = 0.9;
      ps->speedEnd = 0.45;
      ps->direction = -pi()/2.0;
      ps->spray = pi()/8.0;
      //ps->collide = true;
      //ps->source = this;
      Animatrix* a = new Animatrix();
      a->startY = -h/2.0;
      ps->addAnimatrix(a);
      static_cast<VisageComplex*>(visage)->add(ps);
    }
  }
}

void Platform::move()
{
  if (period <= 0)
    return;
  const double p = static_cast<double>(elapsed % period) / static_cast<double>(period);
  const double a = 2.0 * pi() * p;
  Vec2D op = position;
  position.x = origin.x + std::cos(a) * radiusx;
  position.y = origin.y + std::sin(a) * radiusy;
  velocity = position - op;
}

void Platform::drawPath()
{
  if (stationary())
    return;

  glColor4d(1.0, 1.0, 0.0, 1.0);
  if (radiusx == 0.0 || radiusy == 0.0)
  {
    glBegin(GL_LINES);
    if (radiusx != 0.0)
    {
      glVertex3d(origin.x-position.x-radiusx, origin.y-position.y, 0.0);
      glVertex3d(origin.x-position.x+radiusx, origin.y-position.y, 0.0);
    }
    else
    {
      glVertex3d(origin.x-position.x, origin.y-position.y-radiusy, 0.0);
      glVertex3d(origin.x-position.x, origin.y-position.y+radiusy, 0.0);
    }
    glEnd();
    return;
  }

  size_t points = 36;//static_cast<size_t>(36.0*radiusx*radiusy);
  glBegin(GL_LINE_LOOP);
  for (size_t i = 0; i < points; ++i)
  {
    double p = static_cast<double>(i) / static_cast<double>(points);
    glVertex3d(origin.x-position.x + radiusx * std::cos((2.0 * pi()) * p), origin.y-position.y + radiusy * std::sin((2.0 * pi() * p)), 0.0);
  }
  glEnd();
}
