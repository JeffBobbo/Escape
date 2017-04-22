#include "ai.h"

#include <cmath>

#include "../main.h"
#include "../visage/allvisage.h"

AI::AI(double a, double b) : Object(0.5, 0.5, a, b), maxSpeed(3.5)
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
