#ifndef INPUT_H_INCLUDE
#define INPUT_H_INCLUDE

#include <stdint.h>

#include "types.h"

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
  millis_t idle();
  millis_t idle(const int b);

  void registerCallbacks();
}

#include "keys.h"
namespace keyboard
{
  bool pressed(const KeyCode id);
  int modifiers(const KeyCode id);
  millis_t idle();
  millis_t idle(const KeyCode id);

  void registerCallbacks();
}

#endif
