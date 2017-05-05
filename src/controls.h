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
    USE,

    // game controls
    PAUSE,
    MUTE_MUSIC, // like I'm going to have music.... lol
    MUTE
  };

  std::string actionToString(const Action a);
  Action actionFromString(const std::string& s);

  KeyCode bind(const Action a);
  void save();
  void init();
}


#endif
