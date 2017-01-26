#include "player.h"

#include "main.h"

Player::Player()
{
  object = new Object();
  VisageComplex* vc = new VisageComplex();
  VisagePolygon* body = VisagePolygon::rectangle(0.2, 0.35);
  body->setColour(0xFFFFFFFF);
  VisagePolygon* head = VisagePolygon::rectangle(0.2, 0.15);
  head->setColour(0xffd291FF);
  Animatrix* ahead = new Animatrix();
  ahead->startY = 0.25;
  head->addAnimatrix(ahead);
  VisagePolygon* hat = VisagePolygon::triangle(0.25, 0.1);
  hat->setColour(0xFF0000FF);
  Animatrix* ahat = new Animatrix();
  ahat->startY = 0.375;
  hat->addAnimatrix(ahat);
  vc->add(hat);
  vc->add(head);
  vc->add(body);
  object->setVisage(vc);
}

void Player::move()
  {
  if (keys['w'])
    object->y += 0.5 * (delta / 1000.0);
  if (keys['s'])
    object->y -= 0.5 * (delta / 1000.0);
  if (keys['a'])
    object->x -= 0.5 * (delta / 1000.0);
  if (keys['d'])
    object->x += 0.5 * (delta / 1000.0);
}
