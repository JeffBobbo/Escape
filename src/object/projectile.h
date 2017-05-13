#ifndef PROJECTILE_H_INCLUDE
#define PROJECTILE_H_INCLUDE

#include "object.h"

#include "../types.h"
#include "../util.h"

class Projectile : public Object
{
public:
  Projectile(const health_t& d, const Vec2D pos, const Vec2D vel, Object* const t, Object* const o);
  virtual ~Projectile() {};

  virtual inline Type type() const { return Type::PROJECTILE; }
  virtual void move();

  inline Object* getTarget() const { return target; }
  inline Object* getOwner() const { return owner; }

private:
  Object* const target;
  Object* const owner;
  health_t damage;
};

#endif
