#include "ai.h"

#include <cmath>

#include "../main.h"
#include "../visage/allvisage.h"
#include "projectile.h"

Follower::Follower(double w, double h, double u, double v)
 : AI(w, h, u, v)
 , maxSpeed(3.5), accelerate(0.1)
 , encountered(false)
{
  visage = VisagePolygon::circle(0.1, 6);
  static_cast<VisagePolygon*>(visage)->setColour(0xAFAFAFFF);
  Animatrix* anim = new Animatrix();
  anim->rotation = pi() * 64.0;
  visage->addAnimatrix(anim);
}

void Follower::idle()
{
}

void Follower::move()
{
  Player* const player = level->getPlayer();
  double dist = distanceSquared(player);
  if (encountered || (dist > 0.3 && dist <= 2.0))
  {
    encountered = true;
    Vec2D v = player->getPosition() - position + Vec2D(0.0, 0.2);
    velocity += v * accelerate;

    double speed = velocity.magnitude();
    if (speed > maxSpeed)
    {
      double mod = maxSpeed / speed;
      velocity *= mod;
      speed = maxSpeed;
    }
  }
  else if (dist > 2.0)
  {
    velocity *= 0.25 * (delta / 1000.0);
  }
  position += velocity * (delta / 1000.0);
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
      Vec2D pos(position.x + std::cos(radians(angle)) * 0.5, position.y + std::sin(radians(angle)) * 0.5);
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
