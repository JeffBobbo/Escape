#ifndef PLAYER_H_INCLUDE
#define PLAYER_H_INCLUDE

#include "main.h"
#include "object.h"

#include "visage/polygon.h"

class Player
{
public:
  Player()
  {
    object = new Object();
    VisagePolygon* vp = VisagePolygon::rectangle(0.2, 0.5);
    vp->setColour(0xFFFFFFFF);
    object->setVisage(vp);
  }
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
