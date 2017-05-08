#ifndef AI_H_INCLUDE
#define AI_H_INCLUDE

#include "object.h"

class AI : public Object
{
public:
  enum class Classification
  {
    FOLLOWER,
    CAMERA,
    TURRET
  };
  AI(double w, double h, double u, double v) : Object(w, h, u, v) {}
  virtual ~AI() {}

  virtual inline Type type() const final { return Type::AI; }
  virtual inline Classification aiType() const = 0;

  virtual void idle() = 0;
  virtual void move() = 0;

private:
};

class Follower : public AI
{
public:
  Follower(double w, double h, double u, double v);
  virtual ~Follower() {};

  virtual inline Classification aiType() const { return Classification::FOLLOWER; }

  virtual void idle();
  virtual void move();
private:
  double maxSpeed;
  double accelerate;
  bool encountered;
};

class Camera : public AI
{
public:
  Camera(double a, double b);
  virtual ~Camera();

  virtual inline Classification aiType() const { return Classification::CAMERA; }

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

  virtual inline Classification aiType() const { return Classification::TURRET; }

  virtual void move();
private:
  millis_t lastFire;
};

#endif
