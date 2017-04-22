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

  inline uint32_t stepCount() const { return steps; }

private:
  bool facingRight;
  millis_t lastMove;
  millis_t startMove;
  millis_t lastUse;
  millis_t lastJump;
  double v;

  uint32_t steps;
};

#endif
