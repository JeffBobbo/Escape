#include "effect.h"

#include "../visage/allvisage.h"

Effect::Effect(Vec2D pos, const millis_t& life, Visage* const vis)
 : Object({0.0, 0.0}, pos)
 , lifespan(life)
{
  setVisage(vis);
}

void Effect::idle()
{
  if (born + lifespan < elapsed)
    death();
}
