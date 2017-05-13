#ifndef PUSHER_H_INCLUDE
#define PUSHER_H_INCLUDE

#include "object.h"
#include "trigger.h"

class Pusher : public Object, public Actuator
{
public:
  Pusher(Vec2D sz, Vec2D pos);
  virtual ~Pusher() {};

  virtual inline Type type() const { return Type::PUSHER; }
  virtual void idle();

  virtual void actuate();

  void setAttributes(double a, double s, double p, double r);
  void createVisage();

private:
  double spray;
  double power;
  double radius;
  bool redirect;
  bool active;
};

#endif
