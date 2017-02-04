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
  int64_t idle();
  int64_t idle(const int b);

  void registerCallbacks();
}

namespace keyboard
{
  bool pressed(const int id);
  int modifiers(const int id);
  int64_t idle();
  int64_t idle(const int id);

  void registerCallbacks();
}

#endif
