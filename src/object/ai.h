#ifndef AI_H_INCLUDE
#define AI_H_INCLUDE

#include "object.h"

class AI : public Object
{
public:
  enum class Classification
  {
    FOLLOWER,
    ADVISOR,
    CAMERA,
    TURRET,
    PATROL
  };
  AI(Vec2D sz, Vec2D pos) : Object(sz, pos) {}
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
  Follower(Vec2D sz, Vec2D pos);
  virtual ~Follower() {};

  virtual inline Classification aiType() const { return Classification::FOLLOWER; }

  virtual void idle() {}
  virtual void move();
private:
  double maxSpeed;
  double accelerate;
protected:
  bool encountered;
};

class Advisor : public Follower
{
public:
  Advisor(Vec2D pos, const std::string&& a, const millis_t life);
  virtual ~Advisor() {};

  virtual inline Classification aiType() const { return Classification::ADVISOR; }

  virtual void idle();
private:
  std::string advice;
  millis_t lifespan;
};

class Camera : public AI
{
public:
  Camera(Vec2D pos);
  virtual ~Camera() {}

  virtual inline Classification aiType() const { return Classification::CAMERA; }

  virtual void idle() {}
  virtual void move();
private:
  double turnRate;
};

class Turret : public Camera
{
public:
  Turret(Vec2D pos);
  virtual ~Turret() {}

  virtual inline Classification aiType() const { return Classification::TURRET; }

  virtual void move();
private:
  millis_t lastFire;
};

class Platform;
class Patrol : public AI
{
public:
  Patrol(Vec2D pos, Platform* p);
  virtual ~Patrol() {}

  virtual inline Classification aiType() const { return Classification::PATROL; }

  virtual void idle() {}
  virtual void move();

  virtual inline Vec2D boundingVolume() const { return Vec2D(size.x/3.0, size.y); }
private:
  Platform* platform;
  bool facingRight;
  millis_t startMove;
  millis_t hit;
};

#endif
