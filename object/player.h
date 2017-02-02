#ifndef PLAYER_H_INCLUDE
#define PLAYER_H_INCLUDE

#include "object.h"

class Player : public Object
{
public:
  Player();
  virtual ~Player()
  {
  }

  virtual inline Type type() const { return Type::PLAYER; }
  virtual void idle();
  virtual void move();

private:
  bool facingRight;
  uint64_t lastMove;
};

#endif
