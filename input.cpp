#include "input.h"

#include "util.h"
#include "gli.h"

bool keys[256] = {0};

struct MouseState
{
  bool button[3];
  int x;
  int y;
  int mod;
  mouse::Wheel wheel;
  double velx;
  double vely;
  int64_t last;
};

MouseState m = {false, false, false, 0, 0, 0, mouse::Wheel::STATIONARY, 0.0, 0.0, 0};

bool mouse::left()   { return m.button[0]; }
bool mouse::middle() { return m.button[1]; }
bool mouse::right()  { return m.button[2]; }
mouse::Wheel mouse::wheel() { return m.wheel; }
int64_t mouse::lastEvent() { return last; }

void mouse::velocity(double& x, double& y)
{
  x = m.velx;
  y = m.vely;
}


void button(const int button, const int state, const int x, const int y)
{
  if (button < 3)
  {
    m.button[button] = state == GLUT_DOWN;
    m.wheel = mouse::Wheel::STATIONARY;
  }
  else
  {
    m.wheel = button == 3 ? mouse::Wheel::UP : mouse::Wheel::DOWN;
  }
  // only update velocity if this event happened at a different time
  // this should stop any funny stuff with multiple events updating the
  // state
  if (last < elapsed)
  {
    m.velx = (x - m.x) / static_cast<double>(last - elapsed);
    m.vely = (y - m.y) / static_cast<double>(last - elapsed);
  }
  m.x = x;
  m.y = y;
  m.mod = glutGetModifiers();
  last = elapsed;
}
void motion(const int x, const int y)
{
  // only update velocity if this event happened at a different time
  // this should stop any funny stuff with multiple events updating the
  // state
  if (last < elapsed)
  {
    m.velx = (x - m.x) / static_cast<double>(last - elapsed);
    m.vely = (y - m.y) / static_cast<double>(last - elapsed);
  }
  m.x = x;
  m.y = y;
  last = elapsed;
}

// unimplemented, glutMouseWheelFunc is unreliable
void scroll(const int wheel, const int direction, const int x, const int y)
{
  (void)wheel;
  (void)direction;
  (void)x;
  (void)y;
}
void mouse::registerCallbacks()
{
  glutMouseFunc(button);
  glutMotionFunc(motion);
  glutPassiveMotionFunc(motion);
  //glutMouseWheelFunc(::scroll);
}

bool keyDown(const int key)
{
  return keys[key];
}
