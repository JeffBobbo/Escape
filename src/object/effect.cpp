#include "effect.h"

#include "../visage/allvisage.h"

Effect::Effect(double u, double v, const millis_t& life, Visage* const vis)
 : Object(0.0, 0.0, u, v)
 , lifespan(life)
{
  setVisage(vis);
}

void Effect::idle()
{
  if (born + lifespan < elapsed)
    death();
}
