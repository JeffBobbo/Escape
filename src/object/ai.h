#ifndef AI_H_INCLUDE
#define AI_H_INCLUDE

#include "object.h"

class AI : public Object
{
public:
  AI(double w, double h, double u, double v);
  virtual ~AI() {}

  virtual inline Type type() const { return Type::AI; }

  virtual void idle();
  virtual void move();

private:
  double maxSpeed;
  double velx, vely;
};

class Camera : public AI
{
public:
  Camera(double a, double b);
  virtual ~Camera();

  virtual void idle();
  virtual void move();
private:
  double turnRate;
};

class Turret : public Camera
{
public:
  Turret(double a, double b);
  virtual ~Turret();

  virtual void move();
private:
  millis_t lastFire;
};

#endif
