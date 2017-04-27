#ifndef AI_H_INCLUDE
#define AI_H_INCLUDE

#include "object.h"

class AI : public Object
{
public:
  AI(double a, double b);
  virtual ~AI() {}

  virtual inline Type type() const { return Type::AI; }

  virtual void idle();
  virtual void move();

private:
  double maxSpeed;
  double velx, vely;
};

class Sentry : public AI
{
public:
  Sentry(double a, double b);
  virtual ~Sentry();

  virtual void idle();
  virtual void move();
private:
  double turnRate;
  double arc;
  double midpoint;
};

#endif
