#ifndef PLAYER_H_INCLUDE
#define PLAYER_H_INCLUDE

#include "main.h"
#include "object.h"

#include "visage/allvisage.h"
#include "visage/animatrix.h"

class Player
{
public:
  Player();
  ~Player()
  {
    delete object;
  }

  void move();
  void draw() { object->draw(); }

private:
  Object* object;
};

#endif
