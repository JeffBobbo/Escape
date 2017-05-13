#ifndef EFFECT_H_INCLUDE
#define EFFECT_H_INCLUDE

#include "object.h"

#include "../types.h"
#include "../util.h"
#include "../visage/visage.h"

class Effect : public Object
{
public:
  Effect(Vec2D pos, const millis_t& life, Visage* const vis);
  virtual ~Effect() {};

  virtual inline Type type() const { return Type::EFFECT; }

  virtual void idle();

private:
  millis_t lifespan;
};

#endif
