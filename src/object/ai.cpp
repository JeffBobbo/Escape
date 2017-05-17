#include "ai.h"

#include <sstream>

#include <cmath>

#include "../main.h"
#include "../visage/allvisage.h"
#include "effect.h"
#include "platform.h"
#include "projectile.h"

Follower::Follower(Vec2D sz, Vec2D pos)
 : AI(sz, pos)
 , maxSpeed(3.0), accelerate(0.05)
 , encountered(false)
{
  visage = VisagePolygon::circle(0.1, 6);
  static_cast<VisagePolygon*>(visage)->setColour(0xAFAFAFFF);
  Animatrix* anim = new Animatrix();
  anim->rotation = pi() * 64.0;
  visage->addAnimatrix(anim);
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

  Object::move();
}

Advisor::Advisor(Vec2D pos, const std::string&& a, const millis_t life)
 : Follower({0.5, 0.5}, pos)
 , advice(a)
 , lifespan(life)
{
  VisageComplex* vc = new VisageComplex();
  vc->add(new VisageTexture(0.5, 0.5, "img/drone.png"));
  {
    ParticleSystem* ps = new ParticleSystem(100, 100);
    ps->object = this;
    ps->setParticleImage("img/particle_soft.png");
    ps->setColours(fromInt(0xF72A2AFF), fromInt(0xF5F538FF));
    ps->lifeMin = 300;
    ps->lifeMax = 500;
    ps->sizeStart = 0.1;
    ps->sizeEnd = 0.0;
    ps->direction = -pi()/2.0;
    ps->spray = 0.0;
    ps->speedStart = 1.0;
    ps->speedEnd = 0.5;
    Animatrix* a = new Animatrix();
    a->startX = -0.15;
    a->startY = -0.20;
    ps->addAnimatrix(a);
    vc->add(ps);
  }
  {
    ParticleSystem* ps = new ParticleSystem(100, 100);
    ps->object = this;
    ps->setParticleImage("img/particle_soft.png");
    ps->setColours(fromInt(0xF72A2AFF), fromInt(0xF5F538FF));
    ps->lifeMin = 300;
    ps->lifeMax = 500;
    ps->sizeStart = 0.1;
    ps->sizeEnd = 0.0;
    ps->direction = -pi()/2.0;
    ps->spray = 0.0;
    ps->speedStart = 1.0;
    ps->speedEnd = 0.5;
    Animatrix* a = new Animatrix();
    a->startX =  0.15;
    a->startY = -0.20;
    ps->addAnimatrix(a);
    vc->add(ps);
  }
  setVisage(vc);
}

void Advisor::idle()
{
  // stay alive while unencountered
  if (!encountered)
    lifespan += delta;

  if (born + lifespan < elapsed)
  {
    death();
    return;
  }

  if (encountered && !attached)
  {
    millis_t lifeRemaining = (born + lifespan) - elapsed;
    Effect* e = new Effect(position + Vec2D(0.0, 0.5), lifeRemaining, new VisageText(advice, "sui_generis.ttf", 12));
    level->insert(SceneGraph::Level::FOREGROUND, e);
    attached = e;
  }
}

Camera::Camera(Vec2D pos)
 : AI({0.4, 0.2}, pos)
 , turnRate(60.0)
{
  delete visage;
  visage = new VisageTexture(0.4, 0.2, "img/camera.png");
  static_cast<VisageTexture*>(visage)->setAtlasSprite("standby");
  angle = 0.0;
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

Turret::Turret(Vec2D pos) : Camera(pos)
{
  delete visage;
  visage = new VisageTexture(1, 1, "img/turret.png");
  static_cast<VisageTexture*>(visage)->setAtlasSprite("standby");
  lastFire = elapsed;
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

Patrol::Patrol(Vec2D pos, Platform* p)
 : AI({1.0, 1.0}, pos)
 , platform(p)
 , facingRight(true)
 , startMove(elapsed)
 , hit(0)
{
  visage = new VisageTexture(1.0, 1.0, "img/character.png");
  static_cast<VisageTexture*>(visage)->setAtlasSprite("stand");

  Animatrix* a = new Animatrix();
  a->startColour = 0x7F7F7FFF;
  visage->addAnimatrix(a);
}

void Patrol::move()
{
  position.y = platform->getPosition().y + (platform->getSize().y/2.0) + (size.y/2.0);

  if (hit != 0)
  {
    millis_t t = elapsed - hit;
    std::stringstream sprite;
    double a = t/500.0;
    if (a > 4.0)
      death();
    sprite << "death" << interpolate(0, 5, std::min(1.0, a));
    VisageTexture* vt = static_cast<VisageTexture*>(visage);
    vt->setAtlasSprite(sprite.str());
    return;
  }

  Player* p = level->getPlayer();

  double nx = position.x, ny = position.y;
  bool run = hitScan(p) == p &&
    (facingRight ? p->getPosition().x > position.x : p->getPosition().x < position.x);
  {
    static const double RUN_SPEED = 3.0;
    static const double WALK_SPEED = 1.0;
    const double SPEED = (run ? RUN_SPEED : WALK_SPEED);
    if (facingRight)
      velocity.x = SPEED;
    else
      velocity.x = -SPEED;
  }

  nx += velocity.x * (delta / 1000.0);

  // make sure we can move here
  Vec2D tv = boundingVolume();
  for (const Object* const o : level->getGraph()->foreground())
  {
    if (o == this) // skip yourself
      continue;
    if (!o->isSolid()) // skip non-solids
      continue;

    Vec2D ov = o->boundingVolume();
    Vec2D op = o->getPosition();
    if (nx+tv.x/2.0 > op.x-ov.x/2.0 &&
        nx-tv.x/2.0 < op.x+ov.x/2.0 &&
        ny+tv.y/2.0 > op.y-ov.y/2.0 &&
        ny-tv.y/2.0 < op.y+ov.y/2.0)
    {
      nx = position.x;
      facingRight = !facingRight;
    }
  }

  if (!dying() && aabbOverlap(p))
  {
    const double a = angleTo(p);
    if (p->getVelocity().y <= 0.0 && a > pi() * (1.0 / 4.0) && a < pi() * (3.0 / 4.0))
    {
      hit = elapsed;
    }
    else
    {
      p->makeImpact(100);
    }
  }

  if (nx-size.x/2.0 < platform->getPosition().x - platform->getSize().x/2.0 ||
      nx+size.x/2.0 > platform->getPosition().x + platform->getSize().x/2.0)
  {
    facingRight = !facingRight;
  }

  // if we move in x, face the correct way, otherwise keep facing the same way
  //facingRight = (nx-position.x) != 0.0 ? (nx-position.x) > 0.0 : facingRight;
  if (nx-position.x == 0.0)
    startMove = 0;
  // otherwise, set it appropriately.
  position.x = nx;
  position.y = ny;

  std::stringstream sprite;
  if (velocity.x != 0.0)
  {
    millis_t index = (elapsed-startMove) / (run ? 100 : 200) % 8;
    sprite << (run ? "run" : "walk") << index;
  }
  else
  {
    sprite << "stand";
  }
  VisageTexture* vt = static_cast<VisageTexture*>(visage);
  vt->setAtlasSprite(sprite.str());
  vt->setFlip(!facingRight);
}
