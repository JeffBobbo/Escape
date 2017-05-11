#ifndef PUSHER_H_INCLUDE
#define PUSHER_H_INCLUDE

#include "object.h"
#include "trigger.h"

class Pusher : public Object, public Actuator
{
public:
  Pusher(double w, double h, double u, double v);
  virtual ~Pusher() {};

  virtual inline Type type() const { return Type::PUSHER; }
  virtual void idle();

  virtual void actuate();

  void setAttributes(double a, double s, double p, double r)
  {
    angle = a;
    spray = s;
    power = p;
    radius = r;
    createVisage();
  }
  void createVisage();

private:
  double spray;
  double power;
  double radius;
  bool redirect;
  bool active;
};

#endif
