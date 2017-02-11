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
    DOOR
  };

  Object(double w = 1.0, double h = 1.0)
  {
    angle = 0.0;
    rotation = 0.0;
    x = 0.0;
    y = 0.0;
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
  {
    Object();
    x = u;
    y = v;
    width = w;
    height = h;
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

class Door : public Wall
{
public:
  Door(double w, double h, double u, double v, bool o)
  : Wall(w, h, u, v)
  {
    trigger = nullptr;
    open = o;
    vOpen = VisagePolygon::rectangle(w, h*0.1);
    static_cast<VisagePolygon*>(vOpen)->setColour(0x7f7f7fFF);
    vClose = visage;
  }
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
  virtual void move();
private:
  Object* trigger;
  bool open;
  Visage* vOpen;
  Visage* vClose;
};

#endif
