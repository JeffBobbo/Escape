#include "particle.h"

#include <GL/gl.h>

#include "../util.h"

double offset = 0.10;
Particle::Particle()
{
  // set position
  {
    double angle = random(-Pi(), Pi());
    pos[0] = offset * std::cos(angle);
    pos[1] = offset * std::sin(angle);
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

  size = 2.5;

  // set a random lifespan
  life = random(1000, 1500);
  age = 0;
}

void ParticleSystem::add()
{
  if (!full())
  {
    *last = Particle();
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
      // apply some Gs
      //p->vel[1] -= 0.0005f*delta;

      // move
      p->pos[0] += p->vel[0] * (delta / 1000.0f);
      p->pos[1] += p->vel[1] * (delta / 1000.0f);
      p->pos[2] += p->vel[2] * (delta / 1000.0f);

      // some colour decay
      p->col[0] *= 1.0f - 0.3f*(delta / 1000.0f);
      p->col[1] *= 1.0f - 0.3f*(delta / 1000.0f);
      p->col[2] *= 1.0f - 0.3f*(delta / 1000.0f);
      p->col[3] *= (1.0f - 0.3f*delta);

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
  size_t num = random(0, 50);
  for (size_t i = 0; i < num; ++i)
    add();
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
  Particle* p = particles;
  while (p != last)
  {
    glPointSize(p->size);
    glBegin(GL_POINTS);
    glColor4fv(p->col);
    glVertex3fv(p->pos);
    ++p;
  }
  glEnd();
}
