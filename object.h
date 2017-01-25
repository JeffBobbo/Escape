#ifndef OBJECT_H_INCLUDE
#define OBJECT_H_INCLUDE

#include "visage/visage.h"

class Object
{
public:
  Object()
  {
    angle = 0.0;
    rotation = 0.0;
    x = 0.0;
    y = 0.0;
    visage = nullptr;
  };

  virtual ~Object()
  {
    delete visage;
  }

  inline void setVisage(Visage* v) { delete visage; visage = v; }

  void draw();

  double angle;
  double rotation;
  double x;
  double y;
  Visage* visage;
};

#endif
