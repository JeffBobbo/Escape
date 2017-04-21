#ifndef OBJECT_H_INCLUDE
#define OBJECT_H_INCLUDE

#include "../types.h"
#include "../visage/allvisage.h"

class Object
{
public:
  enum class Type
  {
    OBJECT = 0,
    PLAYER,
    PLATFORM,
    DOOR,
    TRIGGER,
    EXIT,
    GRID
  };

  Object(double w = 0.0, double h = 0.0, double u = 0.0, double v = 0.0)
  {
    angle = 0.0;
    rotation = 0.0;
    x = u;
    y = v;
    width = w;
    height = h;
    visage = nullptr;
    phase = -1;
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
  virtual inline double distanceSquared(const Object* const o) const
  {
    return (x-o->x)*(x-o->x)+(y-o->y)*(y-o->y);
  }
  virtual inline double distance(const Object* const o) const { return std::sqrt(distanceSquared(o)); }
  virtual bool aabbOverlap(const Object* const o) const;


  double angle;
  double rotation;
  double x;
  double y;
  double width;
  double height;
  phase_t phase;
  Visage* visage;
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
  virtual ~Exit() {};

  virtual inline Type type() const { return Type::EXIT; }

  inline std::string getNext() const { return name; }

private:
  std::string name;
};

#include <iostream>
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

#endif
