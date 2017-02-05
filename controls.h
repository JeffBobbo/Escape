#ifndef CONTROLS_H_INCLUDE
#define CONTROLS_H_INCLUDE

#include <string>

#include "keys.h"

namespace controls
{
  enum class Action
  {
    NONE,
    // movement
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    CROUCH,
    WALK_MODIFIER,

    // interaction
    PHASE_UP,
    PHASE_DOWN,
    USE,

    // game controls
    PAUSE,
    MUTE_MUSIC, // like I'm going to have music.... lol
    MUTE_ALL
  };

  KeyCode bind(const Action a);
  void init();
}


#endif
