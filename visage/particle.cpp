#include "particle.h"

#include <GL/gl.h>

#include "../util.h"

double offset = 0.10;
Particle::Particle()
{
  // set position
  {
    double angle = random(-Pi(), Pi());
    double o = random(0.0, offset);
    pos[0] = o * std::cos(angle);
    pos[1] = o * std::sin(angle);
    pos[2] = 0.0f;
  }

  // create random direction
  double dir = random(-Pi(), Pi());
  double speed = random(-0.05f, 0.05f);
  vel[0] = speed * std::cos(dir);
  vel[1] = speed * std::sin(dir);
  vel[2] = 0.0;

  // create random colour
  col[0] = 0.8f;
  col[1] = random(0.0f, 0.75f);
  col[2] = 0.1f;
  col[3] = 1.0f;

  age = 0;
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
    last->size = sizeStart;
    //last->sizeEnd = sizeEnd < 0.0f ? sizeStart : sizeEnd;
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
        p->vel[1] -= 0.0005f * delta;

      // move
      p->pos[0] += p->vel[0] * (delta / 1000.0f);
      p->pos[1] += p->vel[1] * (delta / 1000.0f);
      p->pos[2] += p->vel[2] * (delta / 1000.0f);

      // interpolate colours
      // do it in HSV space because it looks better, but is slightly slower
      RGBA col = rgba({
        interpolate(hsva0.h, hsva1.h, prog),
        interpolate(hsva0.s, hsva1.s, prog),
        interpolate(hsva0.v, hsva1.v, prog),
        interpolate(hsva0.a, hsva1.a, prog)
      });
      p->col[0] = col.r;
      p->col[1] = col.g;
      p->col[2] = col.b;
      p->col[3] = col.a;

      if (sizeEnd >= 0.0f)
        p->size = interpolate(sizeStart, sizeEnd, prog);

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
