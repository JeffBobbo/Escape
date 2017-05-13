#include "projectile.h"

#include <string>

#include "player.h"
#include "../visage/allvisage.h"

Projectile::Projectile(const health_t& d, const Vec2D pos, const Vec2D vel, Object* const t, Object* const o)
  : Object({0.05, 0.05}, pos)
  , target(t), owner(o)
  , damage(d)
{
  velocity = vel;
  visage = new VisageComplex();
  VisagePolygon* vp = VisagePolygon::circle(0.05, 6);
  vp->setColour(0xFF0000FF);
  static_cast<VisageComplex*>(visage)->add(vp);

  ParticleSystem* ps = new ParticleSystem(200, 100);
  ps->setParticleImage("img/particle_soft.png");
  ps->setColours(fromInt(0xFF0000FF), fromInt(0x7FFF0000));
  ps->lifeMin = 500.0;
  ps->lifeMax = 750.0;
  ps->sizeStart = 0.04;
  ps->sizeEnd = 0.025;
  ps->speedStart = vel.magnitude();//2;
  ps->speedEnd = vel.magnitude();//1;
  ps->direction = (-vel).angle();
  ps->spray = 0;
  ps->offsetX = 0.1;
  ps->offsetY = 0.1;
  static_cast<VisageComplex*>(visage)->add(ps);
}

void Projectile::move()
{
  Vec2D oldpos = position;
  Object::move();

  if (age() > 1000)
  {
    seppuku = true;
    return;
  }

  Object* collide = collisionTest();
  if (collide != nullptr && collide != target)
  {
    seppuku = true;
    return;
  }

  if (target && (collide == target || target->intersect(oldpos, position)))
  {
    if (target->type() == Object::Type::PLAYER)
    {
      Player* const p = static_cast<Player*>(target);
      p->makeImpact(damage);//, owner);
      death();
    }
  }
}
