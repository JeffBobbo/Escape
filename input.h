#ifndef INPUT_H_INCLUDE
#define INPUT_H_INCLUDE

#include <stdint.h>

namespace mouse
{
  enum class Wheel
  {
    STATIONARY,
    UP,
    DOWN
  };
  bool left();
  bool middle();
  bool right();
  Wheel wheel();
  void velocity(double& x, double& y);
  int64_t lastEvent();

  void registerCallbacks();
}

struct KeyState
{
  int key;
  int x;
  int y;
  int mod;
};

extern bool keys[256];

bool keyDown(const int key);
inline bool keyUp(const int key) { return !keyDown(key); }

#endif
