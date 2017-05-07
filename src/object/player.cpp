#include "player.h"

#include <algorithm>

#include "../main.h"
#include "../input.h"
#include "../visage/allvisage.h"
#include "../visage/animatrix.h"

#include "../controls.h"

Player::Player(double a, double b)
  : Object(1.0, 1.0, a, b)
{
  VisageTexture* vt = new VisageTexture(1.0, 1.0, "img/character.png");
  setVisage(vt);

  facingRight = true;
  lastMove = elapsed;
  startMove = 0;
  lastUse = elapsed;
  lastJump = elapsed;

  health = 100;
  maxHealth = 100;
  lastDamage = elapsed;
  lastHeal = elapsed;

  steps = 0;
  jumps = 0;
}

#include <iostream>
void Player::idle()
{
  if (health != maxHealth)
  {
    static const millis_t TICKS_PER_HEALTH = 200;
    millis_t last = std::max(lastHeal, lastDamage + 1000);
    if (elapsed - last > TICKS_PER_HEALTH)
    {
      health_t toHeal = (elapsed - last) / TICKS_PER_HEALTH;
      if (health < maxHealth)
        health += toHeal;
      else
        health -= toHeal;
      lastHeal = last + TICKS_PER_HEALTH * toHeal;
    }
  }
}

#include <algorithm>
#include <sstream>
void Player::move()
{
  if (elapsed - lastUse > 200 && keyboard::pressed(controls::bind(controls::Action::USE)))
  {
    lastUse = elapsed;
    for (auto o : level->getGraph()->foreground())
    {
      Trigger* t = dynamic_cast<Trigger*>(o);
      if (!t)
        continue;
      if (aabbOverlap(o))
        t->set();
    }
  }

  // only jump if v==0.0, that means we're on the ground
  if (velocity.y == 0.0) // TODO: Fix this
  {
    if (keyboard::pressed(controls::bind(controls::Action::JUMP)))
    {
      velocity.y = -gravity()/1.5;
      lastMove = elapsed;
      lastJump = elapsed;
      ++jumps;
    }
  }

  double nx = x;
  double ny = y;

  const bool walk = keyboard::pressed(controls::bind(controls::Action::WALK_MODIFIER));
  {
    static const double ACCELERATION = 30.0;
    const double a = ACCELERATION * (delta / 1000.0) * velocity.y == 0.0 ? 1.0 : 0.125;
    const bool l = keyboard::pressed(controls::bind(controls::Action::MOVE_LEFT));
    const bool r = keyboard::pressed(controls::bind(controls::Action::MOVE_RIGHT));
    if (l && !r)
    {
      if (velocity.y == 0.0)
        velocity.x = -std::min((walk ? 1.5 : 3.0), std::abs(velocity.x) + a);
      else
        velocity.x = std::max(-4.5, velocity.x - a);
    }
    else if (r && !l)
    {
      if (velocity.y == 0.0)
        velocity.x =  std::min((walk ? 1.5 : 3.0), std::abs(velocity.x) + a);
      else
        velocity.x = std::min(4.5, velocity.x + a);
    }
    else if (velocity.y > 0.0)
    {
      const double t = -velocity.y / gravity(); // how long it'll take to reach the top
      const double dvx = (-velocity.x / t) * (delta / 1000.0);
      velocity.x = std::abs(velocity.x) < std::abs(dvx) ? 0.0 : (velocity.x + dvx);
    }
    else
      velocity.x = std::abs(velocity.x) < a ? 0.0 : (velocity.x < 0.0 ? -1.0 : 1.0) * (std::abs(velocity.x) - a);
  }

  nx += velocity.x * (delta / 1000.0);
  velocity.y += gravity() * (delta / 1000.0);
  ny += velocity.y * (delta / 1000.0);

  // make sure we can move here
  Vec2D tv = boundingVolume();
  for (const Object* const o : level->getGraph()->foreground())
  {
    if (o == this) // skip yourself
      continue;
    if (!o->isSolid()) // skip non-solids
      continue;

    Vec2D ov = o->boundingVolume();
    // test y first
    if (x+tv.x/2.0 > o->x-ov.x/2.0 &&
        x-tv.x/2.0 < o->x+ov.x/2.0 &&
        ny+tv.y/2.0 > o->y-ov.y/2.0 &&
        ny-tv.y/2.0 < o->y+ov.y/2.0)
    {
      ny = velocity.y <= 0 ? o->y+ov.y/2.0+tv.y/2.0 : y;
      velocity.y = 0.0;
    }
    if (nx+tv.x/2.0 > o->x-ov.x/2.0 &&
        nx-tv.x/2.0 < o->x+ov.x/2.0 &&
        ny+tv.y/2.0 > o->y-ov.y/2.0 &&
        ny-tv.y/2.0 < o->y+ov.y/2.0)
      nx = x;
  }

  // if we move in x, face the correct way, otherwise keep facing the same way
  facingRight = (nx-x) != 0.0 ? (nx-x) > 0.0 : facingRight;
  if (nx-x != 0.0)
  {
    lastMove = elapsed;
    if (startMove == 0)
      startMove = lastMove;
  }
  else
  {
    startMove = 0;
  }
  // otherwise, set it appropriately.
  x = nx;
  y = ny;

  std::stringstream sprite;
  if (velocity.y != 0.0)
  {
    sprite << "jumpfall" << std::min(((elapsed - lastJump) / 150), 5);
  }
  else if (velocity.x != 0.0)
  {
    static millis_t lastIndex = -1;
    millis_t index = (elapsed-startMove) / (walk ? 200 : 100) % 8;
    sprite << (walk ? "walk" : "run") << index;
    if (index != lastIndex && (index == 0 || index == 4))
      ++steps;
    lastIndex = index;
  }
  else
  {
    if (elapsed - lastMove > 2500)
      sprite << "stand";
    else
      sprite << "stance" << std::abs(((elapsed / 200) % 7) - 3);
  }
  VisageTexture* vt = static_cast<VisageTexture*>(visage);
  vt->setAtlasSprite(sprite.str());
  vt->setFlip(!facingRight);
}

void Player::death()
{
  Checkpoint* cp = level->getCheckpoint();
  if (cp)
  {
    x = cp->x;
    y = cp->y;
    health = cp->health;
    maxHealth = cp->maxHealth;
    lastDamage = elapsed + cp->lastDamage;
    lastHeal = elapsed + cp->lastHeal;
  }
  else
  {
    glutLeaveMainLoop();
  }
}

void Player::makeImpact(const health_t& damage)
{
  health -= damage;
  lastDamage = elapsed;
  if (health <= 0)
    death();
}
