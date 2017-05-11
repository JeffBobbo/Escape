#ifndef OBJECT_H_INCLUDE
#define OBJECT_H_INCLUDE

#include "../types.h"
#include "../util.h"
#include "../visage/allvisage.h"

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
    PUSHER,
    EFFECT
  };

  Object(double w = 0.0, double h = 0.0, double u = 0.0, double v = 0.0);

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
    return position.distanceSquared(o->getPosition());
  }
  inline double distance(const Object* const o) const { return std::sqrt(distanceSquared(o)); }
  virtual inline Vec2D boundingVolume() const { return Vec2D(width, height); }
  bool aabbOverlap(const Object* const o) const;
  bool pointInside(const Vec2D& v) const;
  Object* hitScan(const Object* const o, const bool ethereal = false) const;
  Object* collisionTest(const bool ethereal = false) const;
  bool intersect(const Vec2D& p0, const Vec2D& p1) const;
  double angleTo(const Object* const o) const;

  inline void setPosition(const Vec2D& p) { position = p; }
  inline const Vec2D& getPosition() const { return position; }
  inline void setVelocity(const Vec2D& v) { velocity = v; }
  inline const Vec2D& getVelocity() const { return velocity; }

  inline millis_t age() const { return elapsed - born; }
  inline bool dying() const { return seppuku; }

  double angle;
  double rotation;
  Vec2D position;
  Vec2D velocity;
  double width;
  double height;
  Visage* visage;
  const millis_t born;

protected:
  bool seppuku;
};

#endif
