#ifndef OBJECT_H_INCLUDE
#define OBJECT_H_INCLUDE

#include "../types.h"
#include "../visage/allvisage.h"

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
    PROJECTILE
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
    phase = -1;
    seppuku = false;
  }

  virtual ~Object()
  {
    if (visage)
      delete visage;
  }

  virtual inline Type type() const { return Type::OBJECT; }
  inline void setVisage(Visage* v) { delete visage; visage = v; }
  virtual void idle();
  virtual void move();
  virtual void draw();

  virtual inline bool isSolid() const { return false; }
  inline double distanceSquared(const Object* const o) const
  {
    return (x-o->x)*(x-o->x)+(y-o->y)*(y-o->y);
  }
  inline double distance(const Object* const o) const { return std::sqrt(distanceSquared(o)); }
  virtual inline Vec2D boundingVolume() const { return Vec2D(width, height); }
  bool aabbOverlap(const Object* const o) const;
  Object* lineOfSight(const Object* const o, const bool ethereal = false) const;
  bool intersect(const Vec2D& p0, const Vec2D& p1) const;
  double angleTo(const Object* const o) const;

  inline millis_t age() const { return elapsed - born; }
  inline bool dying() const { return seppuku; }

  double angle;
  double rotation;
  double x;
  double y;
  Vec2D velocity;
  double width;
  double height;
  phase_t phase;
  Visage* visage;
  const millis_t born;

protected:
  bool seppuku;
};

class Platform : public Object
{
public:
  Platform(double w, double h, double u, double v, double rx = 0.0, double ry = 0.0, millis_t p = 0)
  : Object(w, h, u, v)
  , radiusx(rx), radiusy(ry)
  , period(p)
  {
    originx = x;
    originy = y;
    visage = VisagePolygon::rectangle(w, h);
    static_cast<VisagePolygon*>(visage)->setColour(0x7f7f7fFF);
    // visage = new VisageTexture(w, h, "img/background/tile1.png");
    // static_cast<VisageTexture*>(visage)->setRepeat(w, h);
  }
  virtual ~Platform() {}

  virtual inline Type type() const { return Type::PLATFORM; }
  virtual inline bool isSolid() const { return true; }
  virtual void move();
private:
  double radiusx;
  double radiusy;
  millis_t period;
  double originx;
  double originy;
};

class Button;
class Door : public Object
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

  inline void link(Button* l) { trigger = l; }

private:
  Button* trigger; // later change this to a Trigger object
  bool open;
  Visage* vOpen;
  Visage* vClose;
};

// turn into a generic trigger class
class Button : public Object
{
public:
  Button(double u, double v, millis_t t);
  virtual ~Button() {};

  virtual inline Type type() const { return Type::TRIGGER; }
  virtual void idle();

  inline void set()
  {
    last = timeout == -1 ? !last : elapsed;
  }

  inline bool on() const
  {
    return timeout == -1 ? last != 0 : elapsed - last < timeout;
  }

private:
  millis_t last;
  millis_t timeout;
};

class Exit : public Object
{
public:
  Exit(double u, double v, const std::string& n);
  virtual ~Exit() {}

  virtual inline Type type() const { return Type::EXIT; }

  inline std::string getNext() const { return name; }

private:
  std::string name;
};

class Checkpoint : public Object
{
public:
  Checkpoint(double u, double v);
  virtual ~Checkpoint() {}

  virtual inline Type type() const { return Type::CHECKPOINT; }

  void activate(const Player* const player);

private:
  health_t hp;
};

class Grid : public Object
{
public:
  Grid(double w, double h, double u, double v, phase_t p);
  virtual ~Grid() {}

  virtual inline Type type() const { return Type::GRID; }
  virtual void idle();
  virtual void draw() { if (!trigger || trigger->on()) Object::draw(); }
  inline void link(Button* l) { trigger = l; }

private:
  phase_t target;
  Button* trigger;
};

class Projectile : public Object
{
public:
  Projectile(const Vec2D& pos, Object* const t);
  virtual ~Projectile() {};

  virtual inline Type type() const { return Type::PROJECTILE; }
  virtual void move();

  inline Object* getTarget() const { return target; }
private:
  Object* const target;
};

#endif
