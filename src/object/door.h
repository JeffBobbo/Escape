#ifndef DOOR_H_INCLUDE
#define DOOR_H_INCLUDE

#include "object.h"
#include "trigger.h"

class Door : public Object, public Actuator
{
public:
  Door(double w, double h, double u, double v, bool o, bool p = false);
  virtual ~Door();

  virtual inline Type type() const { return Type::DOOR; }
  virtual inline bool isSolid() const { return !open; }
  virtual void idle();

  virtual void actuate();

private:
  bool open;
  Visage* vOpen;
  Visage* vClose;
};

#endif
