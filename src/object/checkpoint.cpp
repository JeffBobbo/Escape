#include "checkpoint.h"

#include "player.h"
#include "../main.h"
#include "../visage/polygon.h"

Checkpoint::Checkpoint(double u, double v, bool s)
  : Object(0.5, 0.5, u, v)
  , spawn(s), active(s)
  , health(100), maxHealth(100)
  , lastDamage(elapsed), lastHeal(elapsed)
{
  if (!spawn)
  {
    visage = VisagePolygon::triangle(0.5, 0.5, 0.0);
    static_cast<VisagePolygon*>(visage)->setColour(0xFF0000FF);
  }
}

void Checkpoint::idle()
{
  Player* p = level->getPlayer();
  if (!active && aabbOverlap(p))
    activate(p);
}

void Checkpoint::activate(const Player* const player)
{
  VisagePolygon* vp = static_cast<VisagePolygon*>(visage);
  /*
  {
    Animatrix* a = new Animatrix();
    a->startColour = 0xFF0000FF;
    a->endColour = 0x00FF00FF;
    a->start = 0;
    a->end = 5000;
    vp->addAnimatrix(a);
  }
  */
  vp->setColour(0x00FF00FF);
  health = player->health;
  maxHealth = player->maxHealth;
  lastDamage = elapsed - player->lastDamage;
  lastHeal = elapsed - player->lastHeal;
  level->setCheckpoint(this);
}
