#include "player.h"

#include "../main.h"
#include "../input.h"
#include "../visage/allvisage.h"
#include "../visage/animatrix.h"

#include "../controls.h"

Player::Player()
{
  /*
  VisageComplex* vc = new VisageComplex();
  VisagePolygon* body = VisagePolygon::rectangle(0.2, 0.35);
  body->setColour(0xFFFFFFFF);
  VisagePolygon* head = VisagePolygon::rectangle(0.2, 0.15);
  head->setColour(0xffd291FF);
  Animatrix* ahead = new Animatrix();
  ahead->startY = 0.25;
  head->addAnimatrix(ahead);
  VisagePolygon* eye = VisagePolygon::rectangle(0.02, 0.02);
  eye->setColour(0x000000FF);
  Animatrix* aeye = new Animatrix();
  aeye->startY = 0.28;
  aeye->startX = 0.075;
  eye->addAnimatrix(aeye);
  VisagePolygon* hat = VisagePolygon::triangle(0.25, 0.1, 1.1);
  hat->setColour(0xFF0000FF);
  Animatrix* ahat = new Animatrix();
  ahat->startY = 0.375;
  hat->addAnimatrix(ahat);
  vc->add(hat);
  vc->add(head);
  vc->add(eye);
  vc->add(body);
  setVisage(vc);

  VisageTexture* vt = new VisageTexture("img/M484SpaceSoldier.png");
  setVisage(vt);
  */
  VisageTexture* vt = new VisageTexture("img/character.png");
  vt->setAtlasSize(9, 8);
  {
    Animatrix* a = new Animatrix();
    a->startColour = 0xFFFFFFFF;
    a->endColour = 0xFF0000FF;
    a->start = 0;
    a->end = 350;
    a->loop = 700;
    vt->addAnimatrix(a);
  }
  {
    Animatrix* a = new Animatrix();
    a->startColour = 0xFF3F3FFF;
    a->endColour = 0xFFFFFFFF;
    a->start = 350;
    a->end = 700;
    a->loop = 700;
    vt->addAnimatrix(a);
  }
  setVisage(vt);

  facingRight = true;
  lastMove = 0;
  v = 0.0;
  phase = 0;
}

void Player::idle()
{
}

#include <algorithm>
void Player::move()
{
  double nx = x;
  double ny = y;

  bool running = false;
  if (keyboard::pressed(controls::bind(controls::Action::JUMP)))
    ny += 0.5 * (delta / 1000.0);
  if (keyboard::pressed(controls::bind(controls::Action::CROUCH)))
    ny -= 0.5 * (delta / 1000.0);
  bool walk = keyboard::pressed(controls::bind(controls::Action::WALK_MODIFIER));
  if (keyboard::pressed(controls::bind(controls::Action::MOVE_LEFT)))
  {
    running = true;
    nx -= (walk ? 0.75 : 1.5) * (delta / 1000.0);
  }
  if (keyboard::pressed(controls::bind(controls::Action::MOVE_RIGHT)))
  {
    running = true;
    nx += (walk ? 0.75 : 1.5) * (delta / 1000.0);
  }
  //v -= 0.00981f * (delta / 1000.0);
  //ny += v;// * (delta / 1000);

  bool good = true;
  // make sure we can move here
  for (const Object* const o : level->getPhaseBase()->foreground())
  {
    if (!o->isSolid()) // skip non-solids
      continue;
    if (nx > o->x - o->width/2.0 && nx < o->x + o->width/2.0 && ny > o->y - o->height/2.0 && ny < o->y + o->height/2.0)
    {
      good = false;
      break;
    }
  }

  if (phase != -1)
  {
    for (const Object* const o : level->getPhase(phase)->foreground())
    {
      if (!o->isSolid()) // skip non-solids
        continue;
      if (nx > o->x - o->width/2.0 && nx < o->x + o->width/2.0 && ny > o->y - o->height/2.0 && ny < o->y + o->height/2.0)
      {
        good = false;
        break;
      }
    }
  }

  if (good)
  {
    // if we move in x, face the correct way, otherwise keep facing the same way
    facingRight = (nx-x) != 0.0 ? (nx-x) > 0.0 : facingRight;
    if (nx-x != 0.0)
      lastMove = elapsed;
    // otherwise, set it appropriately.
    x = nx;
    y = ny;
  }

  int32_t sprite;
  if (running) // if we're running, use a running sprite (index 5-12)
  {
    sprite = (elapsed / 100) % 8 + 4;
  }
  else
  {
    uint64_t t = elapsed - lastMove;
    if (t > 2500)
    {
      if (t > 10000)
      {
        sprite = interpolate(18, 23, std::min(1.0, (t-10000)/500.0));
      }
      else
      {
        sprite = 64;
      }
    }
    else
      sprite = std::abs(((elapsed / 200) % 7) - 3);
  }
  VisageTexture* vt = static_cast<VisageTexture*>(visage);
  vt->setAtlasSprite(sprite % 8, sprite / 8);
  vt->setFlip(!facingRight);
}
