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
  v = 0.0;
  phase = 0;

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
  if (health < maxHealth)
  {
    static const millis_t TICKS_PER_HEALTH = 200;
    millis_t last = std::max(lastHeal, lastDamage);
    if (TICKS_PER_HEALTH < elapsed - last)
    {
      health_t toHeal = (elapsed - last) / TICKS_PER_HEALTH;
      health += toHeal;
      lastHeal = last + TICKS_PER_HEALTH * toHeal;
    }
  }
}

#include <algorithm>
#include <sstream>
void Player::move()
{
  double nx = x;
  double ny = y;

  static millis_t lastPhase = 0;
  if (elapsed - lastPhase > 500 && keyboard::pressed(controls::bind(controls::Action::PHASE_UP)) && level->numPhases())
  {
    phase = phase+1 % level->numPhases();
    lastPhase = elapsed;
  }
  else if (elapsed - lastPhase > 500 && keyboard::pressed(controls::bind(controls::Action::PHASE_DOWN)) && level->numPhases())
  {
    phase = (phase-1+level->numPhases()) % level->numPhases();
    lastPhase = elapsed;
  }

  if (elapsed - lastUse > 200 && keyboard::pressed(controls::bind(controls::Action::USE)))
  {
    lastUse = elapsed;
    for (auto o : level->getPhaseBase()->foreground())
    {
      if (o->type() != Object::Type::TRIGGER)
        continue;
      Button* b = static_cast<Button*>(o);
      if (aabbOverlap(b))
      {
        b->set();
      }
    }
    if (level->numPhases())
    {
      for (auto o : level->getPhase(phase)->foreground())
      {
        if (o->type() != Object::Type::TRIGGER)
          continue;
        Button* b = static_cast<Button*>(o);
        if (aabbOverlap(b))
        {
          b->set();
        }
      }
    }
  }

  bool move = false; // do we want moving animation
  // only jump if v==0.0, that means we're on the ground
  if (v == 0.0 && keyboard::pressed(controls::bind(controls::Action::JUMP)))
  {
    v = gravity()/1.5;
    lastMove = elapsed;
    lastJump = elapsed;
    ++jumps;
  }

  //if (keyboard::pressed(controls::bind(controls::Action::CROUCH)))
  //  ny -= 0.5 * (delta / 1000.0);
  bool walk = keyboard::pressed(controls::bind(controls::Action::WALK_MODIFIER));
  if (keyboard::pressed(controls::bind(controls::Action::MOVE_LEFT)))
  {
    move = true;
    nx -= (walk ? 1.5 : 3.0) * (delta / 1000.0);
  }
  if (keyboard::pressed(controls::bind(controls::Action::MOVE_RIGHT)))
  {
    move = true;
    nx += (walk ? 1.5 : 3.0) * (delta / 1000.0);
  }

  v -= gravity() * (delta / 1000.0);
  ny += v;// * (delta / 1000.0);

  // make sure we can move here
  for (const Object* const o : level->getPhaseBase()->foreground())
  {
    if (o == this) // skip yourself
      continue;
    if (!o->isSolid()) // skip non-solids
      continue;

    // test y first
    if (x+width/4.0 > o->x-o->width/2.0 &&
        x-width/4.0 < o->x+o->width/2.0 &&
        ny+height/2.0 > o->y-o->height/2.0 &&
        ny-height/2.0 < o->y+o->height/2.0)
    {
      ny = v <= 0 ? o->y+o->height/2.0+height/2.0 : y;
      v = 0.0;
    }
    if (nx+width/4.0 > o->x-o->width/2.0 &&
        nx-width/4.0 < o->x+o->width/2.0 &&
        ny+height/2.0 > o->y-o->height/2.0 &&
        ny-height/2.0 < o->y+o->height/2.0)
      nx = x;
  }

  if (phase != -1 && level->getPhase(phase))
  {
    for (const Object* const o : level->getPhase(phase)->foreground())
    {
      if (!o->isSolid()) // skip non-solids
        continue;
      if (x+width/4.0 > o->x-o->width/2.0 &&
          x-width/4.0 < o->x+o->width/2.0 &&
          ny+height/2.0 > o->y-o->height/2.0 &&
          ny-height/2.0 < o->y+o->height/2.0)
      {
        ny = v <= 0 ? o->y+o->height/2.0+height/2.0 : y;
        v = 0.0;
      }
      if (nx+width/4.0 > o->x-o->width/2.0 &&
          nx-width/4.0 < o->x+o->width/2.0 &&
          ny+height/2.0 > o->y-o->height/2.0 &&
          ny-height/2.0 < o->y+o->height/2.0)
          nx = x;
    }
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
  if (v != 0.0)
  {
    sprite << "jumpfall" << std::min(((elapsed - lastJump) / 150), 5);
  }
  else if (move)
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
