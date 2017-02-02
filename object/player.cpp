#include "player.h"

#include "../main.h" // keys
#include "../visage/allvisage.h"
#include "../visage/animatrix.h"

Player::Player()
{
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

  /*
  VisageTexture* vt = new VisageTexture("img/M484SpaceSoldier.png");
  setVisage(vt);
  */
}

void Player::idle()
{
}

void Player::move()
{
  double nx = x;
  double ny = y;

  if (keys['w'])
    ny += 0.5 * (delta / 1000.0);
  if (keys['s'])
    ny -= 0.5 * (delta / 1000.0);
  if (keys['a'])
    nx -= 0.5 * (delta / 1000.0);
  if (keys['d'])
    nx += 0.5 * (delta / 1000.0);

  bool good = true;
  // make sure we can move here
  for (const Object* const o : graph->foreground())
  {
    if (!o->isSolid()) // skip non-solids
      continue;
    if (nx > o->x - o->width/2.0 && nx < o->x + o->width/2.0 && ny > o->y - o->height/2.0 && ny < o->y + o->height/2.0)
    {
      good = false;
      break;
    }
  }

  if (good)
  {
    x = nx;
    y = ny;
  }
}
