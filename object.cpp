#include "object.h"

#include "main.h"

#include <GL/gl.h>
#include <GL/freeglut.h>

void Object::draw()
{
  // reset
  glLoadIdentity();

  // transformations
  glTranslatef(x, y, 0.0);
  glRotatef(angle, 0.0, 0.0, 1.0);

  // rotation
  angle += rotation * (delta / 1000.0);
  while (angle > 360.0)
    angle -= 360.0;

  visage->draw();
}
