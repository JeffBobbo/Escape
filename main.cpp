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
  ~Shape()
  {
    for (Vec2D* p : v)
      delete p;
  }
  uint32_t col;
  double a;
  double r;
  double x;
  double y;
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
  glClearColor(0.0, 0.0, 0.0, 1.0);

  for (auto s : shapes)
  {
    glLoadIdentity(); // clear any transformations

    // apply any needed transformations
    glTranslatef(s->x, s->y, 0.0);
    glRotatef(s->a, 0.0, 0.0, 1.0);

    // move this into the object's move/idle function
    s->a += s->r; // roughly 60rpm
    while (s->a > 360.0)
      s->a -= 360.0;

    glBegin(GL_POLYGON);
    // set the colour
    glColor4f(
      ((s->col >> 24) & 255) / 255.0, // r
      ((s->col >> 16) & 255) / 255.0, // g
      ((s->col >> 8 ) & 255) / 255.0, // b
      ((s->col      ) & 255) / 255.0  // a
    );
    for (auto v : s->v)
      glVertex3f(v->x, v->y, 0.0);
    glEnd();
  }
  glutSwapBuffers();
}

void update()
{
}

int main(int argc, char** argv)
{
  seed();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  window = glutCreateWindow(title);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glShadeModel(GL_FLAT);
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(1.5);
  glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

  Shape* s = new Shape(0x7f7f7fFF, 0.0);
  s->v.push_back(new Vec2D(0.0, 0.0));
  s->v.push_back(new Vec2D(2.0, 0.0));
  s->v.push_back(new Vec2D(2.0, 0.25));
  s->v.push_back(new Vec2D(0.0, 0.25));
  s->x = -1;
  s->y = -1;
  shapes.push_back(s);
  s = new Shape(0xFF00007F, 2.5);
  s->v.push_back(new Vec2D( 0.0, -0.2));
  s->v.push_back(new Vec2D(-0.2,  0.0));
  s->v.push_back(new Vec2D( 0.0,  0.2));
  s->v.push_back(new Vec2D( 0.2,  0.0));
  shapes.push_back(s);
  s->x = -0.75;
  s->y =  0.75;
  s = new Shape(0x00BCFF7F, 0.0);
  s->v.push_back(new Vec2D(0.0, 0.0));
  s->v.push_back(new Vec2D(1.0, 0.0));
  s->v.push_back(new Vec2D(1.0, 1.0));
  s->v.push_back(new Vec2D(0.0, 1.0));
  s->x = 0.2;
  s->y = -1.0;
  shapes.push_back(s);
  s = new Shape(0xBC00007F, 0.0);
  s->v.push_back(new Vec2D(0.0, 0.0));
  s->v.push_back(new Vec2D(1.0, 0.0));
  s->v.push_back(new Vec2D(1.0, 1.0));
  s->v.push_back(new Vec2D(0.0, 1.0));
  s->x = -0.4;
  s->y = -1.0;
  shapes.push_back(s);


  // set the display function callback
  glutDisplayFunc(draw);
  // set the idle (update) callback
  glutIdleFunc(draw);

  // begin glut loop
  glutMainLoop();

  // cleanup
  for (Shape* s : shapes)
    delete s;
  return 0;
}
