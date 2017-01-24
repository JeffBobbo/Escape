// g++ main.cpp -Wall -Wextra -std=c++11 -lglut -lGL -o main.out

#include <iostream>
#include <stdint.h>
#include <vector>
#include <cmath>

#include "GL/freeglut.h"
#include "GL/gl.h"

const char* const title = "OpenGL Playing";

const double BG_R = 1.0;
const double BG_G = 1.0;
const double BG_B = 1.0;
const double BG_A = 1.0;

constexpr double Pi() { return std::atan2(0.0, -1.0); };

struct Vec2D
{
  Vec2D(double u, double v) : x(u), y(v) {};
  double x;
  double y;
};

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

void draw()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(BG_R, BG_G, BG_B, BG_A);

  for (auto s : shapes)
  {
    glLoadIdentity(); // clear any transformations
    glTranslatef(0.0, 0.0, 0.0);
    // rotate the state
    glRotatef(s->a, 0.0, 0.0, 1.0);

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
  glFlush();
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
  glutCreateWindow(title);

  Shape* s = new Shape();
  s->v.push_back(new Vec2D( 0.0, -0.5));
  s->v.push_back(new Vec2D(-0.5,  0.0));
  s->v.push_back(new Vec2D( 0.0,  0.5));
  s->v.push_back(new Vec2D( 0.5,  0.0));
  shapes.push_back(s);
  s = new Shape(0x0000FFFF, -30);
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
