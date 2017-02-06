#ifndef PARTICLE_H_INCLUDE
#define PARTICLE_H_INCLUDE

#include <stdint.h>

#include "visage.h"

#include "../colour.h"

class Particle
{
public:
  Particle();

  float pos[3];
  float vel[3];
  float col[4];
  float size;

  int64_t life;
  int64_t age;
};

class ParticleSystem : public Visage
{
public:
  ParticleSystem(size_t m, size_t r)
    : max(m)
    , count(0.0)
    , rate(r)
    , lifeMin(1000), lifeMax(0)
    , sizeStart(0.0f), sizeEnd(0.0f)
    , direction(0.0), spray(2.0*pi())
    , speedStart(0.0), speedEnd(0.0)
    , gravity(false)
    , tex(0)
  {
    // allocate all the memory up front
    // this'll make memory usage initially higher, but means less allocations
    // during run time (thus faster execution)
    particles = new Particle[max];
    last = particles;
    end = particles + max;
  }
  virtual ~ParticleSystem()
  {
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

  void loadParticleImage(const std::string& file);

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
  int64_t lifeMin;
  int64_t lifeMax;
  float sizeStart;
  float sizeEnd;
  double direction;
  double spray;
  double speedStart;
  double speedEnd;
  bool gravity;

  GLuint tex;
};

#endif
