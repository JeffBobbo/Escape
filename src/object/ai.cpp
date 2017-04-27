#include "ai.h"

#include <cmath>

#include "../main.h"
#include "../visage/allvisage.h"

AI::AI(double a, double b) : Object(0.1, 0.1, a, b), maxSpeed(3.5)
{
  visage = VisagePolygon::circle(0.1, 6);
  static_cast<VisagePolygon*>(visage)->setColour(0xAFAFAFFF);
  Animatrix* anim = new Animatrix();
  anim->rotation = pi() * 64.0;
  visage->addAnimatrix(anim);
  phase = -1;
  velx = 0.0;
  vely = 0.0;
}

void AI::idle()
{
}

void AI::move()
{
  Player* const player = level->getPlayer();
  double dist = distanceSquared(player);
  if (dist > 0.3 && dist <= 2.0)
  {
    double px = player->x - x;
    double py = player->y - y + 0.2;

    double accelerate = 1.0 / 10.0;
    double nx = px * accelerate;
    double ny = py * accelerate;

    velx += nx;
    vely += ny;

    double speed = std::sqrt(velx*velx + vely*vely);
    if (speed > maxSpeed)
    {
      double mod = maxSpeed / speed;
      velx *= mod;
      vely *= mod;
      speed = maxSpeed;
    }
  }
  else if (dist > 2.0)
  {
    velx -= velx * 0.75 * (delta / 1000.0);
    vely -= vely * 0.75 * (delta / 1000.0);
  }
  x += velx * (delta / 1000.0);
  y += vely * (delta / 1000.0);
}

Sentry::Sentry(double a, double b) : AI(a, b), turnRate(45.0), arc(pi()/3.0), midpoint(-pi()/2.0)
{
  visage = VisagePolygon::rectangle(0.1, 0.5);
  static_cast<VisagePolygon*>(visage)->setColour(0xAFAFAFFF);
  phase = -1;
  angle = midpoint;
}

Sentry::~Sentry()
{
}

void Sentry::idle()
{
}

void Sentry::move()
{
  if (!level)
    return;
  const Player* const target = level->getPlayer();
  if (!target)
    return;

  double tx = target->x;
  double ty = target->y;
  double ox = x;
  double oy = y;
  double a = degrees(std::atan2(oy - ty, ox - tx) + pi()/2.0) + 180.0;;

  double d = a - (angle + 180.0);
  while (d > 180.0)
    d -= 360.0;
  while (d < -180.0)
    d += 360.0;

  double na = (d < 0.0 ? -1.0 : 1.0) * std::min(std::abs(d), turnRate * (delta / 1000.0));
  angle += na;
}
