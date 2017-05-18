#ifndef PARTICLE_H_INCLUDE
#define PARTICLE_H_INCLUDE

#include <stdint.h>

#include "visage.h"

#include "../colour.h"
#include "../gli.h"

class Object;
class Particle
{
public:
  Particle();

  float pos[3];
  float vel[3];
  float col[4];
  float size;

  millis_t life;
  millis_t age;
};

class ParticleSystem : public Visage
{
public:
  ParticleSystem(size_t m, size_t r);
  virtual ~ParticleSystem()
  {
    if (particles)
      delete[] particles;
  }

  virtual inline Type type() const { return Type::PARTICLE; }

  inline void setGravity(bool g) { gravity = g; }
  void setColours(RGBA c0, RGBA c1);

  inline bool empty() const { return particles == last; }
  inline bool full()  const { return end == last; }
  void add();
  void erase(Particle* p);

  void update();

  virtual void draw();

  void setParticleImage(const std::string& file) { particle = file; }

private:
  Particle* particles;
  const size_t max;
  Particle* last;
  Particle* end;

  // how many particles to add
  // adds up fractions so that we can create a slow stream of particles (e.g., 1 a second)
  // or even longer time periods
  // see ParticleSystem::add()
  double count;
public:

  // store the HSVA version, allows faster interpolation
  HSVA hsva0;
  HSVA hsva1;
  size_t rate; // per s
  millis_t lifeMin;
  millis_t lifeMax;
  double sizeStart;
  double sizeEnd;
  double direction;
  double spray;
  double speedStart;
  double speedEnd;
  double gravity;
  double offsetX;
  double offsetY;
  bool rectangle;
  bool collide;
  Object* source;
  bool initialVelocity;
  bool inheritVelocity;

  std::string particle;
};

#endif
