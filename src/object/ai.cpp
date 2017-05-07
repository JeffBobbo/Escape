#include "ai.h"

#include <cmath>

#include "../main.h"
#include "../visage/allvisage.h"

AI::AI(double w, double h, double u, double v) : Object(w, h, u, v), maxSpeed(3.5)
{
  visage = VisagePolygon::circle(0.1, 6);
  static_cast<VisagePolygon*>(visage)->setColour(0xAFAFAFFF);
  Animatrix* anim = new Animatrix();
  anim->rotation = pi() * 64.0;
  visage->addAnimatrix(anim);
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

Camera::Camera(double a, double b) : AI(0.4, 0.1, a, b), turnRate(60.0)
{
  delete visage;
  visage = new VisageTexture(0.4, 0.1, "img/camera.png");
  static_cast<VisageTexture*>(visage)->setAtlasSprite("standby");
  angle = 0.0;
}

Camera::~Camera()
{
}

void Camera::idle()
{
}

void Camera::move()
{
  const Object* const target = level->getPlayer();

  if (!target)
    return;

  if (hitScan(target) != target)
  {
    static_cast<VisageTexture*>(visage)->setAtlasSprite("standby");
    return;
  }


  double d = degrees(angularDifference(angleTo(target), radians(angle)));

  double na = (d < 0.0 ? -1.0 : 1.0) * std::min(std::abs(d), turnRate * (delta / 1000.0));
  angle += na;
  if (std::abs(angularDifference(angleTo(target), radians(angle))) < pi() / 6.0)
    static_cast<VisageTexture*>(visage)->setAtlasSprite("active");
  else
    static_cast<VisageTexture*>(visage)->setAtlasSprite("standby");
}

Turret::Turret(double a, double b) : Camera(a, b)
{
  delete visage;
  visage = new VisageTexture(1, 1, "img/turret.png");
  static_cast<VisageTexture*>(visage)->setAtlasSprite("standby");
  lastFire = elapsed;
}

Turret::~Turret()
{
}

void Turret::move()
{
  Camera::move();

  Object* const target = level->getPlayer();
  if (!target)
    return;

  Object* const hit = hitScan(target);
  const bool inArc = std::abs(angularDifference(angleTo(target), radians(angle))) < pi() / 6.0;

  if (hit != target)
  {
    static_cast<VisageTexture*>(visage)->setAtlasSprite("standby");
    return;
  }

  static const millis_t RECOIL = 100;

  if (elapsed - lastFire > RECOIL)
  {
    if (distance(target) < 10.0 && inArc)
    {
      static const double speed = 10.0;
      const double a = angle * random(0.975, 1.025);
      // fire!
      Vec2D pos(x + std::cos(radians(angle)) * 0.5, y + std::sin(radians(angle)) * 0.5);
      Vec2D vel(speed * std::cos(radians(a)), speed * std::sin(radians(a)));
      Projectile* p = new Projectile(1, pos, vel, target, this);
      lastFire = elapsed;
      level->insert(SceneGraph::Level::NPC, p);
      static_cast<VisageTexture*>(visage)->setAtlasSprite("firing");
    }
    else
    {
      static_cast<VisageTexture*>(visage)->setAtlasSprite("active");
    }
  }
  else
  {
    static_cast<VisageTexture*>(visage)->setAtlasSprite("firing");
  }
}
