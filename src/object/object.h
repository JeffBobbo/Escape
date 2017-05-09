#ifndef OBJECT_H_INCLUDE
#define OBJECT_H_INCLUDE

#include "../types.h"
#include "../visage/allvisage.h"

#include "trigger.h"
//#include "actuator.h"

class Player;
class Object
{
public:
  enum class Type
  {
    OBJECT = 0,
    PLAYER,
    AI,
    PLATFORM,
    DOOR,
    TRIGGER,
    EXIT,
    CHECKPOINT,
    GRID,
    PROJECTILE,
    PUSHER
  };

  Object(double w = 0.0, double h = 0.0, double u = 0.0, double v = 0.0) : velocity(), born(elapsed)
  {
    angle = 0.0;
    rotation = 0.0;
    x = u;
    y = v;
    width = w;
    height = h;
    visage = nullptr;
    seppuku = false;
  }

  virtual ~Object()
  {
    if (visage)
      delete visage;
  }

  virtual inline Type type() const { return Type::OBJECT; }

  inline void setVisage(Visage* v) { if (visage) delete visage; visage = v; }
  virtual void idle();
  virtual void move();
  virtual void draw() final;
  virtual void death();

  virtual inline bool isSolid() const { return false; }
  inline double distanceSquared(const Object* const o) const
  {
    return (x-o->x)*(x-o->x)+(y-o->y)*(y-o->y);
  }
  inline double distance(const Object* const o) const { return std::sqrt(distanceSquared(o)); }
  virtual inline Vec2D boundingVolume() const { return Vec2D(width, height); }
  bool aabbOverlap(const Object* const o) const;
  bool pointInside(const Vec2D& v) const;
  Object* hitScan(const Object* const o, const bool ethereal = false) const;
  Object* collisionTest(const bool ethereal = false) const;
  bool intersect(const Vec2D& p0, const Vec2D& p1) const;
  double angleTo(const Object* const o) const;

  inline void setVelocity(const Vec2D& v) { velocity = v; }

  inline millis_t age() const { return elapsed - born; }
  inline bool dying() const { return seppuku; }

  double angle;
  double rotation;
  double x;
  double y;
  Vec2D velocity;
  double width;
  double height;
  Visage* visage;
  const millis_t born;

protected:
  bool seppuku;
};

class Platform : public Object
{
public:
  Platform(double w, double h, double u, double v, double rx = 0.0, double ry = 0.0, millis_t p = 0);
  virtual ~Platform() {}

  virtual inline Type type() const { return Type::PLATFORM; }
  virtual inline bool isSolid() const { return true; }
  virtual void move();

  inline bool stationary() const { return !period || (radiusx == 0.0 && radiusy == 0.0); }
  void drawPath();

private:
  double radiusx;
  double radiusy;
  millis_t period;
  double originx;
  double originy;
};

class Button;
class Door : public Object, public Actuator
{
public:
  Door(double w, double h, double u, double v, bool o, bool p = false);
  virtual ~Door()
  {
    if (vOpen)
    {
      delete vOpen;
      vOpen = nullptr;
    }
    if (vClose)
    {
      delete vClose;
      vClose = nullptr;
    }
    visage = nullptr;
  }

  virtual inline Type type() const { return Type::DOOR; }
  virtual inline bool isSolid() const { return !open; }
  virtual void idle();

  virtual void actuate();

private:
  bool open;
  Visage* vOpen;
  Visage* vClose;
};

// turn into a generic trigger class
class Button : public Object, public Trigger
{
public:
  Button(double u, double v, millis_t t);
  virtual ~Button() {};

  virtual inline Type type() const { return Type::TRIGGER; }
  virtual void idle();

  virtual inline bool on() const
  {
    return timeout == -1 ? last != 0 : elapsed - last < timeout;
  }

  virtual inline void set()
  {
    last = timeout == -1 ? !last : elapsed;
    if (actuator)
      actuator->actuate();
  }

private:
  millis_t last;
  millis_t timeout;
};

class Exit : public Object, public Actuator
{
public:
  Exit(double u, double v, const std::string& n = "");
  virtual ~Exit() {}

  virtual inline Type type() const { return Type::EXIT; }

  inline std::string getNext() const { return name; }
  virtual void actuate() {}
  bool active() const;

private:
  std::string name;
};

class Checkpoint : public Object
{
  friend Player;
public:
  Checkpoint(double u, double v, bool s = false);
  virtual ~Checkpoint() {}

  virtual inline Type type() const { return Type::CHECKPOINT; }

  virtual void idle();

  void activate(const Player* const player);


private:
  const bool spawn;
  bool active;
  health_t health;
  health_t maxHealth;
  millis_t lastDamage;
  millis_t lastHeal;
};

/*
class Grid : public Object
{
public:
  Grid(double w, double h, double u, double v);
  virtual ~Grid() {}

  virtual inline Type type() const { return Type::GRID; }
  virtual void idle();
  virtual void draw() { if (!trigger || trigger->on()) Object::draw(); }
  inline void link(Button* l) { trigger = l; }

private:
  Button* trigger;
};
*/

class Projectile : public Object
{
public:
  Projectile(const health_t& d, const Vec2D& pos, const Vec2D& vel, Object* const t, Object* const o);
  virtual ~Projectile() {};

  virtual inline Type type() const { return Type::PROJECTILE; }
  virtual void move();

  inline Object* getTarget() const { return target; }
  inline Object* getOwner() const { return owner; }

private:
  Object* const target;
  Object* const owner;
  health_t damage;
};

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
