#ifndef OBJECT_H_INCLUDE
#define OBJECT_H_INCLUDE

#include "../visage/visage.h"
#include "../visage/polygon.h"

class Object
{
public:
  enum class Type
  {
    OBJECT = 0,
    WALL,
    PLAYER,
    PLATFORM,
    DOOR,
    TRIGGER,
    EXIT
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
  int16_t phase;
  Visage* visage;
};

class Wall : public Object
{
public:
  Wall(double w, double h, double u, double v)
  : Object(w, h, u, v)
  {
    visage = VisagePolygon::rectangle(w, h);
    static_cast<VisagePolygon*>(visage)->setColour(0x7f7f7fFF);
  }
  virtual ~Wall() {}
  virtual inline Type type() const { return Type::WALL; }
  virtual inline bool isSolid() const { return true; }
};

class Platform : public Wall
{
public:
  Platform(double w, double h, double u, double v, double rx, double ry, int64_t p)
  : Wall(w, h, u, v)
  , radiusx(rx), radiusy(ry)
  , period(p)
  {
    originx = x;
    originy = y;
  }
  virtual ~Platform() {}

  virtual inline Type type() const { return Type::PLATFORM; }
  virtual void move();
private:
  double radiusx;
  double radiusy;
  int64_t period;
  double originx;
  double originy;
};

class Button;
class Door : public Wall
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
  Button(double u, double v, int64_t t);
  virtual ~Button() {};

  virtual inline Type type() const { return Type::TRIGGER; }
  virtual void idle();

  inline void set() { last = timeout == -1 ? !last : elapsed; }

  inline bool on() const
  {
    return timeout == -1 ? last : elapsed - last < timeout;
  }

private:
  int64_t last;
  int64_t timeout;
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

#endif
