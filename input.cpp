#include "input.h"

#include <cstring> // std::memset

#include "util.h"
#include "gli.h"

struct MouseButton
{
  int x;
  int y;
  int mod;
  bool pressed;
  int64_t last;
};

struct MouseState
{
  MouseButton buttons[3];
  mouse::Wheel wheel;
  int x;
  int y;
  double velx;
  double vely;
  int64_t last;
};

MouseState m;

bool mouse::left()   { return m.buttons[0].pressed; }
bool mouse::middle() { return m.buttons[1].pressed; }
bool mouse::right()  { return m.buttons[2].pressed; }
mouse::Wheel mouse::wheel() { return m.wheel; }
int64_t mouse::idle() { return m.last; }
int64_t mouse::idle(const int b) { return m.buttons[b].last; }

void mouse::velocity(double& x, double& y)
{
  x = m.velx;
  y = m.vely;
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
void button(const int button, const int state, const int x, const int y)
{
  if (button < 3)
  {
    m.buttons[button].x = x;
    m.buttons[button].y = y;
    m.buttons[button].mod = glutGetModifiers();
    m.buttons[button].pressed = state == GLUT_DOWN;
    m.buttons[button].last = elapsed;
  }
  else
  {
    if (state == GLUT_DOWN)
      m.wheel = button == 3 ? mouse::Wheel::UP : mouse::Wheel::DOWN;
    else
      m.wheel = mouse::Wheel::STATIONARY;
  }
  // just pass off to the motion callback
  motion(x, y);
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
  std::memset(m.buttons, 0, sizeof m.buttons);
  m.wheel = mouse::Wheel::STATIONARY;
  m.x = m.y = 0;
  m.velx = m.vely = 0.0;
  m.last = 0;


  glutMouseFunc(button);
  glutMotionFunc(motion);
  glutPassiveMotionFunc(motion);
  //glutMouseWheelFunc(::scroll);
}


/******************************************************************************/
/* KEYBOARD */
/******************************************************************************/
struct KeyState
{
  bool pressed;
  int mod;
  int64_t last;
};
struct KeyboardState
{
  KeyState keys[256];
  int64_t last;
};
KeyboardState k;

bool keyboard::pressed(const int id) { return k.keys[id].pressed; }
int keyboard::modifiers(const int id) { return k.keys[id].mod; }
int64_t keyboard::idle() { return last; }
int64_t keyboard::idle(const int id) { return k.keys[id].last; }

#include <iostream>
void kb_press(const unsigned char key, const int x, const int y)
{
  // leaving these bits out for now
  // we don't particularly need the mouse location of a key press
  // if we /really/ need it, it can be queried from the mouse state
  // it may be slightly inaccurate, due to the differing callbacks being called
  // (which would be order dependent), but anything else would involve
  // complicating the structure of KeyboardState, and we most likely don't need it.

  // use (void)x to suppress unused variable warnings with a void-op
  (void)x;
  (void)y;
  k.keys[key].pressed = true;
  k.keys[key].mod = glutGetModifiers();
  k.keys[key].last = elapsed;
}
void kb_release(const unsigned char key, const int x, const int y)
{
  // leaving these bits out for now
  // we don't particularly need the mouse location of a key press
  // if we /really/ need it, it can be queried from the mouse state
  // it may be slightly inaccurate, due to the differing callbacks being called
  // (which would be order dependent), but anything else would involve
  // complicating the structure of KeyboardState, and we most likely don't need it.

  // use (void)x to suppress unused variable warnings with a void-op
  (void)x;
  (void)y;
  k.keys[key].pressed = false;
  k.keys[key].mod = glutGetModifiers();
  k.keys[key].last = elapsed;
}
void keyboard::registerCallbacks()
{
  // not trivial is initialise KeyboardState with the declaration
  // so do it here
  std::memset(k.keys, 0, sizeof k.keys);
  k.last = 0;

  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(kb_press);
  glutKeyboardUpFunc(kb_release);
}
