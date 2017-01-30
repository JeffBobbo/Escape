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
  ParticleSystem(size_t m, size_t r) : max(m), rate(r), gravity(false)
  {
    // allocate all the memory up front
    // this'll make memory usage initially higher, but means less allocations
    // during run time (thus faster execution)
    particles = new Particle[max];
    last = particles;
    end = particles + max;
  }
  ~ParticleSystem()
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

private:
  Particle* particles;
  const size_t max;
  Particle* last;
  Particle* end;

  // store the HSVA version, allows faster interpolation
  HSVA hsva0;
  HSVA hsva1;
  size_t rate; // per ms
  bool gravity;

};

#endif
