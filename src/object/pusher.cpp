#include "pusher.h"

#include <string>

#include "player.h"
#include "../main.h"
#include "../util.h"
#include "../visage/particle.h"

Pusher::Pusher(double w, double h, double u, double v)
  : Object(w, h, u, v), Actuator()
  , spray(0.0), power(1.0)
  , redirect(true)
  , active(true)
{
  setAttributes(pi()/2.0, 0.0, 0.1, w);
  createVisage();
}

void Pusher::idle()
{
  if (!active)
    return;

  Player* p = level->getPlayer();

  if (!aabbOverlap(p))
    return;

  double s = random(-spray/2.0, spray/2.0);
  Vec2D v(std::cos(radians(angle)+s) * power, std::sin(radians(angle)+s) * power);
  if (redirect)
    p->velocity = v;
  else
    p->velocity += v;
}

void Pusher::actuate()
{
  active = trigger->on();
  if (active)
    setVisage(nullptr);
  else
    createVisage();
}

void Pusher::createVisage()
{
  ParticleSystem* ps = new ParticleSystem(200, 100);
  ps->setParticleImage("img/particle_soft.png");
  ps->setColours(fromInt(0xC4C4C4FF), fromInt(0xFFFFFF00));
  ps->lifeMin = 25.0 * power;
  ps->lifeMax = 50.0 * power;
  ps->sizeStart = 0.4 * radius;
  ps->sizeEnd = 0.2 * radius;
  ps->speedStart = 0.2 * power;
  ps->speedEnd = 0.1 * power;
  ps->direction = 0.0;//theta;
  ps->spray = spray;
  ps->offsetX = radius - (std::max(ps->sizeStart, ps->sizeEnd)) / 2.0;
  ps->offsetY = radius - (std::max(ps->sizeStart, ps->sizeEnd)) / 2.0;
  ps->rectangle = true;
  //ps->collide = true;
  //ps->source = this;
  setVisage(ps);
}
