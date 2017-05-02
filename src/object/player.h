#ifndef PLAYER_H_INCLUDE
#define PLAYER_H_INCLUDE

#include "object.h"

#include <iostream>

class Player : public Object
{
public:
  Player(double a = 0.0, double b = 0.0);
  virtual ~Player() {}

  virtual inline Type type() const { return Type::PLAYER; }
  virtual void idle();
  virtual void move();

  virtual inline Vec2D boundingVolume() const { return Vec2D(width/3.0, height); }

  inline uint32_t stepCount() const { return steps; }
  inline uint32_t jumpCount() const { return jumps; }

  inline const health_t& getHealth() const { return health; }
  inline const health_t& getMaxHealth() const { return maxHealth; }
  inline double getHealthPercentage() const
  {
    return static_cast<double>(health) / static_cast<double>(maxHealth);
  }
  inline bool isAlive() const { return health > 0; }
  void deltaHealth(const health_t& delta) { health += delta; }
  void makeImpact(const health_t& damage) { health -= damage; lastDamage = elapsed; }

private:
  bool facingRight;
  millis_t lastMove;
  millis_t startMove;
  millis_t lastUse;
  millis_t lastJump;
  double v;

  health_t health;
  health_t maxHealth;
  millis_t lastDamage;
  millis_t lastHeal;

  uint32_t steps;
  uint32_t jumps;
};

#endif
