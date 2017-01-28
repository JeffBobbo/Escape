#ifndef PLAYER_H_INCLUDE
#define PLAYER_H_INCLUDE

#include "main.h"
#include "object.h"

#include "visage/allvisage.h"
#include "visage/animatrix.h"

class Player : public Object
{
public:
  Player();
  virtual ~Player()
  {
  }

  virtual inline Type type() const { return Type::PLAYER; }
  virtual void idle() { move(); }
  virtual void move();
};

#endif
