#include "particle.h"

#include "../gli.h"

#include "../util.h"
#include "../imageloader.h"

double offset = 0.1;
Particle::Particle()
{
  age = 0;
}

ParticleSystem::ParticleSystem(size_t m, size_t r)
  : max(m)
  , count(0.0)
  , rate(r)
  , lifeMin(1000), lifeMax(0)
  , sizeStart(0.0f), sizeEnd(0.0f)
  , direction(0.0), spray(2.0*pi())
  , speedStart(0.0), speedEnd(0.0)
  , gravity(false)
  , offsetX(0.0), offsetY(0.0)
  , rectangle(false)
{
  // allocate all the memory up front
  // this'll make memory usage initially higher, but means less allocations
  // during run time (thus faster execution)
  particles = new Particle[max];
  last = particles;
  end = particles + max;
}


void ParticleSystem::setColours(RGBA c0, RGBA c1)
{
  hsva0 = hsva(c0);
  hsva1 = hsva(c1);
}

void ParticleSystem::add()
{
  if (!full())
  {
    *last = Particle();
    if (lifeMax == 0)
      last->life = lifeMin;
    else
      last->life = random(lifeMin, lifeMax);
    last->size = static_cast<float>(sizeStart);

    // set position
    if (rectangle)
    {
      last->pos[0] = static_cast<float>(random(-offsetX/2.0, offsetX/2.0));
      last->pos[1] = static_cast<float>(random(-offsetY/2.0, offsetY/2.0));
    }
    else
    {
      double angle = random(-pi(), pi());
      double ox = random(0.0, offsetX);
      double oy = random(0.0, offsetY);
      last->pos[0] = static_cast<float>(ox * std::cos(angle));
      last->pos[1] = static_cast<float>(oy * std::sin(angle));
    }
    last->pos[2] = 0.0f;

    RGBA c = rgba(hsva0);
    last->col[0] = static_cast<float>(c.r);
    last->col[1] = static_cast<float>(c.g);
    last->col[2] = static_cast<float>(c.b);
    last->col[3] = static_cast<float>(c.a);
    // create random direction
    double dir = direction + random(-spray/2.0, spray/2.0);
    last->vel[0] = static_cast<float>(speedStart * std::cos(dir));
    last->vel[1] = static_cast<float>(speedStart * std::sin(dir));
    last->vel[2] = 0.0f;

    ++last;
  }
}
void ParticleSystem::erase(Particle* p)
{
  if (!empty())
    *p = *(--last);
}

#include <iostream>
void ParticleSystem::update()
{
  Particle* p = particles;
  while (p != last)
  {
    p->age += delta;

    if (p->age < p->life)
    {
      double prog = p->age / static_cast<double>(p->life);

      if (gravity) // apply some Gs
        p->vel[1] -= static_cast<float>(::gravity() * delta);

      const double a = std::atan2(p->vel[1], p->vel[0]);
      const double s = interpolate(speedStart, speedEnd, prog);
      p->vel[0] = static_cast<float>(s * std::cos(a));
      p->vel[1] = static_cast<float>(s * std::sin(a));

      // move
      p->pos[0] += p->vel[0] * (delta / 1000.0f);
      p->pos[1] += p->vel[1] * (delta / 1000.0f);

      // interpolate colours
      // do it in HSV space because it looks better, but is slightly slower
      RGBA col = rgba({
        interpolate(hsva0.h, hsva1.h, prog),
        interpolate(hsva0.s, hsva1.s, prog),
        interpolate(hsva0.v, hsva1.v, prog),
        interpolate(hsva0.a, hsva1.a, prog)
      });
      p->col[0] = static_cast<float>(col.r);
      p->col[1] = static_cast<float>(col.g);
      p->col[2] = static_cast<float>(col.b);
      p->col[3] = static_cast<float>(col.a);

      if (sizeEnd >= 0.0f)
        p->size = static_cast<float>(interpolate(sizeStart, sizeEnd, prog));

      ++p;
    }
    else
    {
      erase(p);
      if (p >= last)
        return;
    }
  }
  // create a random number of particles
  count += (rate / 1000.0) * delta;
  while (count > 1.0)
  {
    add();
    count -= 1.0;
  }
}

void ParticleSystem::draw()
{
  update();

  /*
  // pass all the vertex and colour data in one go
  glVertexPointer(3, GL_FLOAT, sizeof(Particle), particles->pos);
  glColorPointer(3, GL_FLOAT, sizeof(Particle), particles->col);

  // enable use of arrays
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  // punch it
  glDrawArrays(GL_POINTS,0,last-particles);

  // disable use of arrays
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  */
  // this is inefficient, what's above is much better, but it's the only way
  // I can specify sizes individually for particles
  Particle* p = particles;
  double col[4];
  glGetDoublev(GL_CURRENT_COLOR, col);
  if (particle.size())
  {
    bindTexture(particle);
    glEnable(GL_TEXTURE_2D);
    while (p != last)
    {
      glColor4d(
        col[0] * p->col[0],
        col[1] * p->col[1],
        col[2] * p->col[2],
        col[3] * p->col[3]
        );
      float x0 = p->pos[0] - p->size/2.0f;
      float y0 = p->pos[1] - p->size/2.0f;
      float x1 = x0 + p->size;
      float y1 = y0 + p->size;
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f);  glVertex3f(x0, y1, 0.0f);
      glTexCoord2f(0.0f, 1.0f);  glVertex3f(x0, y0, 0.0f);
      glTexCoord2f(1.0f, 1.0f);  glVertex3f(x1, y0, 0.0f);
      glTexCoord2f(1.0f, 0.0f);  glVertex3f(x1, y1, 0.0f);
      glEnd();
      ++p;
    }
    glDisable(GL_TEXTURE_2D);
  }
  else
  {
    while (p != last)
    {
      glPointSize(p->size);
      glBegin(GL_POINTS);
      glColor4fv(p->col);
      glVertex3fv(p->pos);
      glEnd();
      ++p;
    }
  }
}
