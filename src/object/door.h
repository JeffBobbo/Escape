#ifndef DOOR_H_INCLUDE
#define DOOR_H_INCLUDE

#include "object.h"
#include "trigger.h"

#include "../util.h"

class Door : public Object, public Actuator
{
public:
  Door(Vec2D sz, Vec2D pos, bool o, bool p = false);
  virtual ~Door();

  virtual inline Type type() const { return Type::DOOR; }
  virtual inline bool isSolid() const { return !open; }
  virtual void idle();

  virtual void actuate();

  void setVisageOpen(Visage* const v);
  void setVisageClose(Visage* const v);

private:
  bool open;
  Visage* vOpen;
  Visage* vClose;
};

#endif
