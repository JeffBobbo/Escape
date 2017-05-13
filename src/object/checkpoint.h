#ifndef CHECKPOINT_H_INCLUDE
#define CHECKPOINT_H_INCLUDE

#include "object.h"
#include "../types.h"
#include "../util.h"

class Player;
class Checkpoint : public Object
{
  friend Player;
public:
  Checkpoint(Vec2D pos, bool s = false);
  virtual ~Checkpoint() {}

  virtual inline Type type() const { return Type::CHECKPOINT; }

  virtual void idle();

  void activate(const Player* const player);


private:
  const bool spawn;
  bool active;
  health_t health;
  health_t maxHealth;
  millis_t lastDamage;
  millis_t lastHeal;
};

#endif
