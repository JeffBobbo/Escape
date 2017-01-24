#include <iostream>
#include <stdint.h>
#include <vector>
#include <cmath>

#include "GL/freeglut.h"
#include "GL/gl.h"

#include "util.h"

const char* const title = "Shifter";

struct Shape
{
  Shape(uint32_t c = 0xFF0000FF, double s = 360/120.)
  {
    col = c;
    a = 0.0;
    r = s;
  }
  uint32_t col;
  double a;
  double r;
  std::vector<Vec2D* > v;
};

std::vector<Shape*> shapes;
int window = -1;
uint64_t frame = 0, elapsed, timebase = 0;

void draw()
{
  ++frame;
  elapsed = glutGet(GLUT_ELAPSED_TIME);

  if (elapsed - timebase > 1000)
  {
    double fps = frame * 1000.0 / (elapsed - timebase);
    timebase = elapsed;
    frame = 0;
    char buf[50];
    sprintf(buf, "%s - FPS: %4.2f", title, fps);
    glutSetWindowTitle(buf);
    timebase = elapsed;
    frame = 0;
  }

  glClear(GL_COLOR_BUFFER_BIT);

  // background is grey
  glClearColor(0.5, 0.5, 0.5, 1.0);

  for (auto s : shapes)
  {
    glLoadIdentity(); // clear any transformations

    // apply any needed transformations
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(s->a, 0.0, 0.0, 1.0);

    // move this into the object's move/idle function
    s->a += s->r; // roughly 60rpm
    while (s->a > 360.0)
      s->a -= 360.0;

    glBegin(GL_POLYGON);
    // set the colour
    glColor3f(
      ((s->col >> 16) & 255) / 255.0,
      ((s->col >> 8 ) & 255) / 255.0,
      ((s->col      ) & 255) / 255.0
    );
    for (auto v : s->v)
      glVertex2f(v->x, v->y);
    glEnd();
  }
  glutSwapBuffers();
}

void update()
{
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  window = glutCreateWindow(title);

  Shape* s = new Shape(0xFF0000FF, 2);
  s->v.push_back(new Vec2D( 0.0, -0.5));
  s->v.push_back(new Vec2D(-0.5,  0.0));
  s->v.push_back(new Vec2D( 0.0,  0.5));
  s->v.push_back(new Vec2D( 0.5,  0.0));
  shapes.push_back(s);
  s = new Shape(0x0000FFFF, -2.5);
  s->v.push_back(new Vec2D( 0.0, -0.25));
  s->v.push_back(new Vec2D(-0.25,  0.0));
  s->v.push_back(new Vec2D( 0.0,  0.25));
  shapes.push_back(s);


  // set the display function callback
  glutDisplayFunc(draw);
  // set the idle (update) callback
  glutIdleFunc(draw);

  // begin glut loop
  glutMainLoop();
  return 0;
}
