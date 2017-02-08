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

#include "keys.h"
namespace keyboard
{
  bool pressed(const KeyCode id);
  int modifiers(const KeyCode id);
  int64_t idle();
  int64_t idle(const KeyCode id);

  void registerCallbacks();
}

#endif
