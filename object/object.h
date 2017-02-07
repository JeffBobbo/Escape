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
    PLATFORM
  };

  Object()
  {
    angle = 0.0;
    rotation = 0.0;
    x = 0.0;
    y = 0.0;
    width = 0.0;
    height = 0.0;
    visage = nullptr;
  }

  virtual ~Object()
  {
    delete visage;
  }

  virtual inline Type type() const { return Type::OBJECT; }
  inline void setVisage(Visage* v) { delete visage; visage = v; }
  virtual void idle();
  virtual void move();
  virtual void draw();

  virtual inline bool isSolid() const { return false; }

  double angle;
  double rotation;
  double x;
  double y;
  double width;
  double height;
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
    visage = VisagePolygon::rectangle(w, h);
    static_cast<VisagePolygon*>(visage)->setColour(0x7f7f7fFF);
    width = w;
    height = h;
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

#endif
