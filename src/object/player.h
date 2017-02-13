#ifndef PLAYER_H_INCLUDE
#define PLAYER_H_INCLUDE

#include "object.h"

class Player : public Object
{
public:
  Player(double a = 0.0, double b = 0.0);
  virtual ~Player()
  {
  }

  virtual inline Type type() const { return Type::PLAYER; }
  virtual void idle();
  virtual void move();

private:
  bool facingRight;
  uint64_t lastMove;
  double v;
};

#endif
